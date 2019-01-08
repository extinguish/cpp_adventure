#include <sys/time.h>
#include <linux/ioctl.h>
#include <linux/rtc.h> // real time clock service
#include "android_alarm.h"
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <zconf.h>

static void format_time(int time, char *buffer) {
    int seconds, minutes, hours, days;

    seconds = time % 60;
    time /= 60;
    minutes = time % 60;
    time /= 60;
    hours = time % 24;
    days = time / 24;
    if (days > 0) {
        sprintf(buffer, "%d days, %02d:%02d:%02d", days, hours, minutes, seconds);
    } else {
        sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
    }
}

static int elapsedRealtimeAlarm(struct timespec *ts) {
    int fd, result;
    fd = open("/dev/alarm", O_RDONLY);
    if (fd < 0) {
        printf("fail to open the dev/alarm file, caused by %s \n", strerror(errno));
        return fd;
    }

    result = ioctl(fd, ANDROID_ALARM_GET_TIME(ANDROID_ALARM_ELAPSED_REALTIME), ts);
    close(fd);

    return result;
}

int uptime_main(int argc __attribute__((unused)), char **argv __attribute__((unused))) {
    float up_time, idle_time;



}
