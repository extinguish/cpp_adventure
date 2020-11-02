//
// Created by guoshichao on 19-6-19.
//

#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#define RANGE_SPECIAL ",;\r\n"

enum ERTSP_RANGE_TIME {
    RTSP_RANGE_SMPTE = 1, // relative to the start of the clip
    RTSP_RANGE_SMPTE_30 = RTSP_RANGE_SMPTE,
    RTSP_RANGE_SMPTE_25,
    RTSP_RANGE_NPT,  // relative to the beginning of the presentation
    RTSP_RANGE_CLOCK, // absolute time, ISO 8601 timestamps, UTC(GMT)
};

enum ERTSP_RANGE_TIME_VALUE {
    RTSP_RANGE_TIME_NORMAL = 1,
    RTSP_RANGE_TIME_NOW, // npt now
    RTSP_RANGE_TIME_NOVALUE, // npt don't set from value: -[npt-time]
};


struct rtsp_header_range_t {
    enum ERTSP_RANGE_TIME type;
    enum ERTSP_RANGE_TIME_VALUE from_value;
    enum ERTSP_RANGE_TIME_VALUE to_value;

    uint64_t from; // ms
    uint64_t to; // ms

    uint64_t time; // range time parameter(in ms), 0 if no value
};

static inline const char *string_token_int(const char *str, int *value) {
    *value = 0;
    while ('0' <= *str && *str <= '9') {
        *value = (*value * 10) + (*str - '0');
        ++str;
    }
    return str;
}

static inline const char *string_token_int64(const char *str, int64_t *value) {
    *value = 0;
    while ('0' <= *str && *str <= '9') {
        *value = (*value * 10) + (*str - '0');
        ++str;
    }
    return str;
}

static uint64_t utc_mktime(const struct tm *t) {
    int mon = t->tm_mon + 1, year = t->tm_year + 1900;

    /* 1..12 -> 11,12,1..10 */
    if (0 >= (int) (mon -= 2)) {
        mon += 12;  /* Puts Feb last since it has leap day */
        year -= 1;
    }

    return ((((uint64_t)
                      (year / 4 - year / 100 + year / 400 + 367 * mon / 12 + t->tm_mday) +
              year * 365 - 719499
             ) * 24 + t->tm_hour /* now have hours */
            ) * 60 + t->tm_min /* now have minutes */
           ) * 60 + t->tm_sec; /* finally seconds */
}


// smpte-time = 1*2DIGIT ":" 1*2DIGIT ":" 1*2DIGIT [ ":" 1*2DIGIT ][ "." 1*2DIGIT ]
// hours:minutes:seconds:frames.subframes
static const char *
rtsp_header_range_smpte_time(const char *str, int *hours, int *minutes, int *seconds, int *frames, int *subframes) {
    const char *p;

    p = string_token_int(str, hours);
    if (*p != ':')
        return NULL;

    p = string_token_int(p + 1, minutes);
    if (*p != ':')
        return NULL;

    p = string_token_int(p + 1, seconds);

    *frames = 0;
    *subframes = 0;
    if (*p == ':') {
        p = string_token_int(p + 1, frames);
    }

    if (*p == '.') {
        p = string_token_int(p + 1, subframes);
    }

    return p;
}

// 3.5 SMPTE Relative Timestamps (p16)
// smpte-range = smpte-type "=" smpte-time "-" [ smpte-time ]
// smpte-type = "smpte" | "smpte-30-drop" | "smpte-25"
// Examples:
//	smpte=10:12:33:20-
//	smpte=10:07:33-
//	smpte=10:07:00-10:07:33:05.01
//	smpte-25=10:07:00-10:07:33:05.01
static int rtsp_header_range_smpte(const char *fields, struct rtsp_header_range_t *range) {
    const char *p;
    int hours, minutes, seconds, frames, subframes;

    p = rtsp_header_range_smpte_time(fields, &hours, &minutes, &seconds, &frames, &subframes);
    if (!p || '-' != *p)
        return -1;

    range->from_value = RTSP_RANGE_TIME_NORMAL;
    range->from = (hours % 24) * 3600 + (minutes % 60) * 60 + seconds;
    range->from = range->from * 1000 + frames % 1000;

    if ('\0' == p[1] || strchr(RANGE_SPECIAL, p[1])) {
        range->to_value = RTSP_RANGE_TIME_NOVALUE;
        range->to = 0;
    } else {
        p = rtsp_header_range_smpte_time(p + 1, &hours, &minutes, &seconds, &frames, &subframes);
        if (!p) {
            return -1;
        }

        range->to_value = RTSP_RANGE_TIME_NORMAL;
        range->to = (hours % 24) * 3600 + (minutes % 60) * 60 + seconds;
        range->to = range->to * 1000 + frames % 1000;
    }

    return 0;
}

// npt-time = "now" | npt-sec | npt-hhmmss
// npt-sec = 1*DIGIT [ "." *DIGIT ]
// npt-hhmmss = npt-hh ":" npt-mm ":" npt-ss [ "." *DIGIT ]
// npt-hh = 1*DIGIT ; any positive number
// npt-mm = 1*2DIGIT ; 0-59
// npt-ss = 1*2DIGIT ; 0-59
static const char *rtsp_header_range_npt_time(const char *str, uint64_t *seconds, int *fraction) {
    const char *p;
    int v1, v2;

    str += strspn(str, " \t");
    p = strpbrk(str, "-\r\n");
    if (!str || (p - str == 3 && 0 == strncasecmp(str, "now", 3))) {
        *seconds = 0; // now
        *fraction = -1;
    } else {
        p = string_token_int64(str, (int64_t *) seconds);
        if (*p == ':') {
            // npt-hhmmss
            p = string_token_int(p + 1, &v1);
            if (*p != ':')
                return NULL;

            p = string_token_int(p + 1, &v2);

            *seconds = *seconds * 3600 + (v1 % 60) * 60 + v2 % 60;
        } else {
            // npt-sec
            //*seconds = hours;
        }

        if (*p == '.')
            p = string_token_int(p + 1, fraction);
        else
            *fraction = 0;
    }

    return p;
}

// utc-time = utc-date "T" utc-time "Z"
// utc-date = 8DIGIT ; < YYYYMMDD >
// utc-time = 6DIGIT [ "." fraction ] ; < HHMMSS.fraction >
static const char *rtsp_header_range_clock_time(const char *str, uint64_t *second, int *fraction) {
    struct tm t;
    const char *p;
    int year, month, day;
    int hour, minute;

    if (!str || 5 != sscanf(str, "%4d%2d%2dT%2d%2d", &year, &month, &day, &hour, &minute))
        return NULL;

    *second = 0;
    *fraction = 0;
    p = string_token_int64(str + 13, (int64_t *) second);
    if (*p == '.') {
        p = string_token_int(p + 1, fraction);
    }

    memset(&t, 0, sizeof(t));
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    *second += utc_mktime(&t);

    return 'Z' == *p ? p + 1 : p;
}

// 3.7 Absolute Time (p18)
// utc-range = "clock" "=" utc-time "-" [ utc-time ]
// Range: clock=19961108T143720.25Z-
// Range: clock=19961110T1925-19961110T2015 (p72)
static int rtsp_header_range_clock(const char *fields, struct rtsp_header_range_t *range) {
    const char *p;
    uint64_t second;
    int fraction;

    p = rtsp_header_range_clock_time(fields, &second, &fraction);
    if (!p || '-' != *p)
        return -1;

    range->from_value = RTSP_RANGE_TIME_NORMAL;
    range->from = second * 1000;
    range->from += fraction % 1000;

    if ('\0' == p[1] || strchr(RANGE_SPECIAL, p[1])) {
        range->to_value = RTSP_RANGE_TIME_NOVALUE;
        range->to = 0;
    } else {
        p = rtsp_header_range_clock_time(p + 1, &second, &fraction);
        if (!p) return -1;

        range->to_value = RTSP_RANGE_TIME_NORMAL;
        range->to = second * 1000;
        range->to += (unsigned int) fraction % 1000;
    }

    return 0;
}

// 3.6 Normal Play Time (p17)
// npt-range = ( npt-time "-" [ npt-time ] ) | ( "-" npt-time )
// Examples:
//	npt=123.45-125
//	npt=12:05:35.3-
//	npt=now-
static int rtsp_header_range_npt(const char *fields, struct rtsp_header_range_t *range) {
    const char *p;
    uint64_t seconds;
    int fraction;

    p = fields;
    if ('-' != *p) {
        p = rtsp_header_range_npt_time(p, &seconds, &fraction);
        if (!p || '-' != *p)
            return -1;

        if (0 == seconds && -1 == fraction) {
            range->from_value = RTSP_RANGE_TIME_NOW;
            range->from = 0L;
        } else {
            range->from_value = RTSP_RANGE_TIME_NORMAL;
            range->from = seconds;
            range->from = range->from * 1000 + fraction % 1000;
        }
    } else {
        range->from_value = RTSP_RANGE_TIME_NOVALUE;
        range->from = 0;
    }

    if ('\0' == p[1] || strchr(RANGE_SPECIAL, p[1])) {
        range->to_value = RTSP_RANGE_TIME_NOVALUE;
        range->to = 0;
    } else {
        p = rtsp_header_range_npt_time(p + 1, &seconds, &fraction);
        if (!p) return -1;

        range->to_value = RTSP_RANGE_TIME_NORMAL;
        range->to = seconds;
        range->to = range->to * 1000 + fraction % 1000;
    }

    return 0;
}


int rtsp_header_range(const char *field, struct rtsp_header_range_t *range) {
    int r = 0;

    range->time = 0L;
    while (field && 0 == r) {
        if (0 == strncasecmp("clock=", field, 6)) {
            range->type = RTSP_RANGE_CLOCK;
            r = rtsp_header_range_clock(field + 6, range);
        } else if (0 == strncasecmp("npt=", field, 4)) {
            range->type = RTSP_RANGE_NPT;
            r = rtsp_header_range_npt(field + 4, range);
        } else if (0 == strncasecmp("smpte=", field, 6)) {
            range->type = RTSP_RANGE_SMPTE;
            r = rtsp_header_range_smpte(field + 6, range);
            if (RTSP_RANGE_TIME_NORMAL == range->from_value)
                range->from = (range->from / 1000 * 1000) + (1000 / 30 * (range->from % 1000)); // frame to ms
            if (RTSP_RANGE_TIME_NORMAL == range->to_value)
                range->to = (range->to / 1000 * 1000) + (1000 / 30 * (range->to % 1000)); // frame to ms
        } else if (0 == strncasecmp("smpte-30-drop=", field, 15)) {
            range->type = RTSP_RANGE_SMPTE_30;
            r = rtsp_header_range_smpte(field + 15, range);
            if (RTSP_RANGE_TIME_NORMAL == range->from_value)
                range->from = (range->from / 1000 * 1000) + (1000 / 30 * (range->from % 1000)); // frame to ms
            if (RTSP_RANGE_TIME_NORMAL == range->to_value)
                range->to = (range->to / 1000 * 1000) + (1000 / 30 * (range->to % 1000)); // frame to ms
        } else if (0 == strncasecmp("smpte-25=", field, 9)) {
            range->type = RTSP_RANGE_SMPTE_25;
            r = rtsp_header_range_smpte(field + 9, range);
            if (RTSP_RANGE_TIME_NORMAL == range->from_value)
                range->from = (range->from / 1000 * 1000) + (1000 / 25 * (range->from % 1000)); // frame to ms
            if (RTSP_RANGE_TIME_NORMAL == range->to_value)
                range->to = (range->to / 1000 * 1000) + (1000 / 25 * (range->to % 1000)); // frame to ms
        } else if (0 == strncasecmp("time=", field, 5)) {
            if (rtsp_header_range_clock_time(field + 5, &range->time, &r))
                range->time = range->time * 1000 + r % 1000;
        }

        field = strchr(field, ';');
        if (field)
            ++field;
    }

    return r;
}

typedef char rfc822_datetime_t[30];
static const char *s_month[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

static const char *s_week[] = {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

const char *rfc822_datetime_format(time_t time, rfc822_datetime_t datetime) {
    int r;
    struct tm *tm = gmtime(&time);

    r = snprintf(datetime, sizeof(rfc822_datetime_t), " %s, %02d %s %04d %02d:%02d:%02d GMT",
                 s_week[(unsigned int) tm->tm_wday % 7],
                 tm->tm_mday,
                 s_month[(unsigned int) tm->tm_mon % 12],
                 tm->tm_year + 1900,
                 tm->tm_hour,
                 tm->tm_min,
                 tm->tm_sec);
    return r > 0 && r < sizeof(rfc822_datetime_t) ? datetime : NULL;
}

#include <string>
#include <map>

class RtspResponse {
public:
    RtspResponse();

    ~RtspResponse();

    void setHeader(const std::string &header);

    void setContentType(const std::string &contentType) { mContentType = contentType; };

    void setConentLength(const std::string &contentLen) { mContentLength = contentLen; }

    void setData(const std::string &key, const std::string &value) {
        mParams.insert(std::pair<std::string, std::string>(key, value));
    }

    void setContent(const std::string &content) { mContent = content; }

    std::string toString();

private:
    std::string mContent;
    std::string mContentType;
    std::string mContentLength;
    std::string mHeader;
    std::map<std::string, std::string> mParams;
};

static const std::string kCRLF = "\r\n";
static const std::string kCONTENTTYPE = "Content-Type: ";
static const std::string kCONTENTLENGTH = "Content-Length: ";
RtspResponse::RtspResponse(){

}

RtspResponse::~RtspResponse(){

}

void RtspResponse::setHeader(const std::string& header){
    mHeader = header;
}

std::string RtspResponse::toString(){
    std::string result;
    result += mHeader + kCRLF;
    std::map<std::string, std::string>::iterator it;
    for(it = mParams.begin(); it != mParams.end(); it++){
        result+=it->first;
        result+=":";
        result+=it->second;
        result+= kCRLF;
    }


    if(mContent.length() != 0){
        result += kCONTENTTYPE + mContentType + kCRLF;
        result += kCONTENTLENGTH + mContentLength + kCRLF;
        result+= kCRLF;
        result += mContent;
    } else {
        result += kCRLF;
    }
    return result;
}


int main(int argc, char **argv) {
    time_t current_time = time(NULL);
    struct tm *timeVal = localtime(&current_time);
    int year = timeVal->tm_year + 1900;
    int month = timeVal->tm_mon;

    int day = timeVal->tm_mday;
    int hour = timeVal->tm_hour;
    int minute = timeVal->tm_min;
    int seconds = timeVal->tm_sec;

    printf("%d - %d - %d : %d - %d - %d\n", year, month, day, hour, minute, seconds);

    rtsp_header_range_t range;
    rtsp_header_range("clock", &range);
    printf("from %lld, to %lld\n", range.from, range.to);

    char timeRange[1024] = {0};
    snprintf(timeRange, sizeof(timeRange), "x-Timeshift_Range: clock=%lu-%lu\r\nx-Timeshift_Range: clock=%lu",
             range.from, range.to, range.to);

    printf("%s\n", timeRange);
    printf("%zu, %zu\n", sizeof(timeRange), strlen(timeRange));

    char rfcTime[1024] = {0};
    rfc822_datetime_format(range.to, rfcTime);
    printf("the rfc time are %s\n", rfcTime);

    printf("------------------>\n");
//    rtsp_header_range_t range1;
//    rtsp_header_range("clock=", &range1);
//    char rangeVal[1024] = {0};
//    snprintf(rangeVal, sizeof(rangeVal), "x-Timeshift_Range: clock=%llu-%llu\r\nx-Timeshift_Range: clock=%llu\r\n",
//             range.from, range.to, range.to);
//    std::string rangeContent(rangeVal);
//    printf("the time range are %s", rangeContent.c_str());


    RtspResponse response;
    response.setHeader("RTSP/1.0 200 OK");
    response.setData("CSeq", "73");

    rtsp_header_range_t range2;
    rtsp_header_range("clock=", &range2);
    char rangeVal2[1024] = {0};
    snprintf(rangeVal2, sizeof(rangeVal2), "clock=%llu-%llu\r\n", range2.from, range2.to);
    char currentTimeVal[1024] = {0};
    snprintf(currentTimeVal, sizeof(rangeVal2), "clock=%llu\r\n", range2.to);
    std::string rangeContent(rangeVal2);
    printf("the time range are %s", rangeContent.c_str());
    response.setData("x-Timeshift_Range: ", rangeContent);
    std::string currentTimeContent(currentTimeVal);
    response.setData("x-Timeshift_Current: ", currentTimeVal);

    std::string resStr = response.toString();
    printf("the final response string are %s\n", resStr.c_str());

    // x-Timeshift_Range:


}

