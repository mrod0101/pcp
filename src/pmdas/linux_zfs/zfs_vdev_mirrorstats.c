#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "zfs_utils.h"
#include "zfs_vdev_mirrorstats.h"

void
zfs_vdev_mirrorstats_refresh(zfs_vdev_mirrorstats_t *vdev_mirrorstats)
{
    char *line = NULL, *mname, *mval;
    char delim[] = " ";
    char fname[MAXPATHLEN];
    FILE *fp;
    size_t len = 0;

    if (zfs_stats_file_check(fname, "vdev_mirror_stats") != 0)
        return;

    fp = fopen(fname, "r");
    if (fp != NULL) {
        while (getline(&line, &len, fp) != -1) {
            mname = strtok(line, delim);
            mval  = strtok(NULL, delim); // not used
            mval  = strtok(NULL, delim);
            if (strcmp(mname, "rotating_linear") == 0) vdev_mirrorstats->rotating_linear = strtoul(mval, NULL, 0);
            else if (strcmp(mname, "rotating_offset") == 0) vdev_mirrorstats->rotating_offset = strtoul(mval, NULL, 0);
            else if (strcmp(mname, "rotating_seek") == 0) vdev_mirrorstats->rotating_seek = strtoul(mval, NULL, 0);
            else if (strcmp(mname, "non_rotating_linear") == 0) vdev_mirrorstats->non_rotating_linear = strtoul(mval, NULL, 0);
            else if (strcmp(mname, "non_rotating_seek") == 0) vdev_mirrorstats->non_rotating_seek = strtoul(mval, NULL, 0);
            else if (strcmp(mname, "preferred_found") == 0) vdev_mirrorstats->preferred_found = strtoul(mval, NULL, 0);
            else if (strcmp(mname, "preferred_not_found") == 0) vdev_mirrorstats->preferred_not_found = strtoul(mval, NULL, 0);
        }
        free(line);
    }
    fclose(fp);
}
