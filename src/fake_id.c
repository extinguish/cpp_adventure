// the id program inside toolbox
// the following are the output of the id program:
// uid=2000(shell) gid=2000(shell) groups=1003(graphics),1004(input),1007(log),1011(adb),1015(sdcard_rw),1028(sdcard_r),3001(net_bt_admin),3002(net_bt),3003(inet),3006(net_bw_stats) context=u:r:shell:s0
// the output even contains the information of the SELinux
// but as the <selinux/selinux.h> we not exposed to out world, so we do not output the
// selinux content info
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

static void print_uid(uid_t uid) {
    struct passwd *psw = getpwuid(uid);
    if (psw) {
        // print out the detailed user name
        printf("%d(%s)", uid, psw->pw_name);
    } else {
        printf("%d", uid);
    }
}

static void print_gid(gid_t gid) {
    struct group *grp = getgrgid(gid);
    if (grp) {
        // print out the group name
        printf("%d(%s)", gid, grp->gr_name);
    } else {
        printf("%d", gid);
    }
}

int main(int argc, char** argv) {
    gid_t list[64];
    int n, max;

    max = getgroups(64, list);
    if (max < 0) {
        max = 0;
    }

    printf("uid=");
    print_uid(getuid());
    printf("; gid=");
    print_gid(getgid());
    if (max) {
        printf(" groups = ");
        print_gid(list[0]);
        for (n = 1; n < max; n++) {
            printf(" , ");
            print_gid(list[n]);
        }
    }
}



