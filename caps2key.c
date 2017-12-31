#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <libudev.h>
#include <sys/select.h>

#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>

// clang-format off
/*
let @c='g=ap€kr=g=ap€kr.g=ap€kr*='
*/

const struct input_event
a_up           = { .type = EV_KEY, .code = KEY_A,         .value = 0},
a_down         = { .type = EV_KEY, .code = KEY_A,         .value = 1},
a_repeat       = { .type = EV_KEY, .code = KEY_A,         .value = 2},
b_up           = { .type = EV_KEY, .code = KEY_B,         .value = 0},
b_down         = { .type = EV_KEY, .code = KEY_B,         .value = 1},
b_repeat       = { .type = EV_KEY, .code = KEY_B,         .value = 2},
d_up           = { .type = EV_KEY, .code = KEY_D,         .value = 0},
d_down         = { .type = EV_KEY, .code = KEY_D,         .value = 1},
d_repeat       = { .type = EV_KEY, .code = KEY_D,         .value = 2},
e_up           = { .type = EV_KEY, .code = KEY_E,         .value = 0},
e_down         = { .type = EV_KEY, .code = KEY_E,         .value = 1},
e_repeat       = { .type = EV_KEY, .code = KEY_E,         .value = 2},
f_up           = { .type = EV_KEY, .code = KEY_F,         .value = 0},
f_down         = { .type = EV_KEY, .code = KEY_F,         .value = 1},
f_repeat       = { .type = EV_KEY, .code = KEY_F,         .value = 2},
h_up           = { .type = EV_KEY, .code = KEY_H,         .value = 0},
h_down         = { .type = EV_KEY, .code = KEY_H,         .value = 1},
h_repeat       = { .type = EV_KEY, .code = KEY_H,         .value = 2},
i_up           = { .type = EV_KEY, .code = KEY_I,         .value = 0},
i_down         = { .type = EV_KEY, .code = KEY_I,         .value = 1},
i_repeat       = { .type = EV_KEY, .code = KEY_I,         .value = 2},
j_up           = { .type = EV_KEY, .code = KEY_J,         .value = 0},
j_down         = { .type = EV_KEY, .code = KEY_J,         .value = 1},
j_repeat       = { .type = EV_KEY, .code = KEY_J,         .value = 2},
k_up           = { .type = EV_KEY, .code = KEY_K,         .value = 0},
k_down         = { .type = EV_KEY, .code = KEY_K,         .value = 1},
k_repeat       = { .type = EV_KEY, .code = KEY_K,         .value = 2},
m_up           = { .type = EV_KEY, .code = KEY_M,         .value = 0},
m_down         = { .type = EV_KEY, .code = KEY_M,         .value = 1},
m_repeat       = { .type = EV_KEY, .code = KEY_M,         .value = 2},
n_up           = { .type = EV_KEY, .code = KEY_N,         .value = 0},
n_down         = { .type = EV_KEY, .code = KEY_N,         .value = 1},
n_repeat       = { .type = EV_KEY, .code = KEY_N,         .value = 2},
p_up           = { .type = EV_KEY, .code = KEY_P,         .value = 0},
p_down         = { .type = EV_KEY, .code = KEY_P,         .value = 1},
p_repeat       = { .type = EV_KEY, .code = KEY_P,         .value = 2},
u_up           = { .type = EV_KEY, .code = KEY_U,         .value = 0},
u_down         = { .type = EV_KEY, .code = KEY_U,         .value = 1},
u_repeat       = { .type = EV_KEY, .code = KEY_U,         .value = 2},
w_up           = { .type = EV_KEY, .code = KEY_W,         .value = 0},
w_down         = { .type = EV_KEY, .code = KEY_W,         .value = 1},
w_repeat       = { .type = EV_KEY, .code = KEY_W,         .value = 2},
backspace_up   = { .type = EV_KEY, .code = KEY_BACKSPACE, .value = 0},
backspace_down = { .type = EV_KEY, .code = KEY_BACKSPACE, .value = 1},
capslock_up    = { .type = EV_KEY, .code = KEY_CAPSLOCK,  .value = 0},
capslock_down  = { .type = EV_KEY, .code = KEY_CAPSLOCK,  .value = 1},
delete_up      = { .type = EV_KEY, .code = KEY_DELETE,    .value = 0},
delete_down    = { .type = EV_KEY, .code = KEY_DELETE,    .value = 1},
down_up        = { .type = EV_KEY, .code = KEY_DOWN,      .value = 0},
down_down      = { .type = EV_KEY, .code = KEY_DOWN,      .value = 1},
end_up         = { .type = EV_KEY, .code = KEY_END,       .value = 0},
end_down       = { .type = EV_KEY, .code = KEY_END,       .value = 1},
enter_up       = { .type = EV_KEY, .code = KEY_ENTER,     .value = 0},
enter_down     = { .type = EV_KEY, .code = KEY_ENTER,     .value = 1},
esc_up         = { .type = EV_KEY, .code = KEY_ESC,       .value = 0},
esc_down       = { .type = EV_KEY, .code = KEY_ESC,       .value = 1},
home_up        = { .type = EV_KEY, .code = KEY_HOME,      .value = 0},
home_down      = { .type = EV_KEY, .code = KEY_HOME,      .value = 1},
lalt_up        = { .type = EV_KEY, .code = KEY_LEFTALT,   .value = 0},
lalt_down      = { .type = EV_KEY, .code = KEY_LEFTALT,   .value = 1},
lalt_repeat      = { .type = EV_KEY, .code = KEY_LEFTALT,   .value = 2},
lctrl_up       = { .type = EV_KEY, .code = KEY_LEFTCTRL,  .value = 0},
lctrl_down     = { .type = EV_KEY, .code = KEY_LEFTCTRL,  .value = 1},
left_up        = { .type = EV_KEY, .code = KEY_LEFT,      .value = 0},
left_down      = { .type = EV_KEY, .code = KEY_LEFT,      .value = 1},
lshift_up      = { .type = EV_KEY, .code = KEY_LEFTSHIFT, .value = 0},
lshift_down    = { .type = EV_KEY, .code = KEY_LEFTSHIFT, .value = 1},
ralt_up        = { .type = EV_KEY, .code = KEY_RIGHTALT,  .value = 0},
ralt_down      = { .type = EV_KEY, .code = KEY_RIGHTALT,  .value = 1},
rctrl_up       = { .type = EV_KEY, .code = KEY_RIGHTCTRL, .value = 0},
rctrl_down     = { .type = EV_KEY, .code = KEY_RIGHTCTRL, .value = 1},
right_up       = { .type = EV_KEY, .code = KEY_RIGHT,     .value = 0},
right_down     = { .type = EV_KEY, .code = KEY_RIGHT,     .value = 1},
semicolon_up   = { .type = EV_KEY, .code = KEY_SEMICOLON, .value = 0},
semicolon_down = { .type = EV_KEY, .code = KEY_SEMICOLON, .value = 1},
semicolon_repeat = { .type = EV_KEY, .code = KEY_SEMICOLON, .value = 2},
tab_up         = { .type = EV_KEY, .code = KEY_TAB,       .value = 0},
tab_down       = { .type = EV_KEY, .code = KEY_TAB,       .value = 1},
up_up          = { .type = EV_KEY, .code = KEY_UP,        .value = 0},
up_down        = { .type = EV_KEY, .code = KEY_UP,        .value = 1};
// clang-format on

int equal(const struct input_event *first, const struct input_event *second) {
    return first->type == second->type && first->code == second->code &&
           first->value == second->value;
}

enum state_e { CAPS_UP, CAPS_DOWN, CAPS_DOWN_MOD_PRESSED, CAPS_DOWN_MAYBE_CHANGE, LCTRL_DOWN, LCTRL_USED, LCTRL_ALT_DOWN, LCTRL_ALT_DOWN_LCTRL_UP };

struct state_s {
    enum state_e fsm;
    __u16 keypressed[32];
    const struct input_event *key_up;
    const struct input_event *key_down;
    struct input_event last_input;
};

__u16 darray[16];
int dlen=0;

void dremove(__u16 x) {
    int found=0;
    for (int i=0; i<dlen; i++) {
        if (darray[i]==x) found=1;
        if (found) darray[i]=darray[i+1];
    }
    dlen--;
}

void dadd(__u16 x) {
    darray[dlen++]=x;
}

int in_array(__u16 x) {
    for (int i=0; i<dlen; i++) {
        if (darray[i]==x) return 1;
    }
    return 0;
}

int eventmap(const struct input_event *input, struct input_event output[], struct state_s *state) {
    if (input->type != EV_KEY) {
        output[0] = *input;
        return 1;
    }

    int k = 0;
    static int capswait;
    static int altwait;
    static int semicolonwait;

    if (equal(input, &capslock_up) && capswait) {
        output[k++] = esc_down;
        output[k++] = esc_up;
        capswait=0;
    } else if (equal(input, &capslock_up)) {
        output[k++] = lctrl_up;
    } else if (equal(input, &capslock_down)) {
        capswait=1;
    }

    else if (semicolonwait && equal(input, &lalt_down)) {
        semicolonwait=2;
        altwait=2;
    } else if (equal(input, &lalt_down)) {
        altwait=1;
    } else if (altwait==2 && equal(input, &lalt_up)) {
        altwait=0;
    } else if (altwait==2 && equal(input, &lalt_repeat)) {
        ;
    }

    else if (equal(input, &semicolon_down) && !in_array(KEY_LEFTSHIFT)) {
        semicolonwait=1;
    } else if (altwait==1 && semicolonwait==1 && equal(input, &semicolon_up)) {
        output[k++] = lalt_down;
        dadd(lalt_down.code);
        altwait=0;
        output[k++] = semicolon_down;
        output[k++] = semicolon_up;
        semicolonwait=0;
    } else if (semicolonwait==1 && equal(input, &semicolon_up)) {
        output[k++] = semicolon_down;
        output[k++] = semicolon_up;
        semicolonwait=0;
    } else if (semicolonwait==2 && equal(input, &semicolon_up)) {
        semicolonwait=0;
    }

    else if (semicolonwait && altwait && (equal(input, &b_down) || equal(input, &b_repeat))) {
        output[k++] = lctrl_down;
        output[k++] = left_down;
        output[k++] = left_up;
        output[k++] = lctrl_up;
        altwait=2;
    } else if (semicolonwait && altwait && (equal(input, &d_down) || equal(input, &d_repeat))) {
        output[k++] = lctrl_down;
        output[k++] = delete_down;
        output[k++] = delete_up;
        output[k++] = lctrl_up;
        altwait=2;
    } else if (semicolonwait && altwait && (equal(input, &f_down) || equal(input, &f_repeat))) {
        output[k++] = lctrl_down;
        output[k++] = right_down;
        output[k++] = right_up;
        output[k++] = lctrl_up;
        altwait=2;
    } else if (semicolonwait && altwait && (equal(input, &h_down) || equal(input, &h_repeat))) {
        output[k++] = lctrl_down;
        output[k++] = backspace_down;
        output[k++] = backspace_up;
        output[k++] = lctrl_up;
        altwait=2;
    }

    else if (semicolonwait && (equal(input, &w_down) || equal(input, &w_repeat))) {
        output[k++] = lctrl_down;
        output[k++] = backspace_down;
        output[k++] = backspace_up;
        output[k++] = lctrl_up;
    } else if (semicolonwait && (equal(input, &a_down) || equal(input, &a_repeat))) {
        output[k++] = home_down;
        output[k++] = home_up;
    } else if (semicolonwait && (equal(input, &b_down) || equal(input, &b_repeat))) {
        output[k++] = left_down;
        output[k++] = left_up;
    } else if (semicolonwait && (equal(input, &d_down) || equal(input, &d_repeat))) {
        output[k++] = delete_down;
        output[k++] = delete_up;
    } else if (semicolonwait && (equal(input, &e_down) || equal(input, &e_repeat))) {
        output[k++] = end_down;
        output[k++] = end_up;
    } else if (semicolonwait && (equal(input, &f_down) || equal(input, &f_repeat))) {
        output[k++] = right_down;
        output[k++] = right_up;
    } else if (semicolonwait && (equal(input, &h_down) || equal(input, &h_repeat))) {
        output[k++] = backspace_down;
        output[k++] = backspace_up;
    } else if (semicolonwait && (equal(input, &i_down) || equal(input, &i_repeat))) {
        output[k++] = tab_down;
        output[k++] = tab_up;
    } else if (semicolonwait && (equal(input, &j_down) || equal(input, &j_repeat))) {
        output[k++] = enter_down;
        output[k++] = enter_up;
    } else if (semicolonwait && (equal(input, &k_down) || equal(input, &k_repeat))) {
        output[k++] = lshift_down;
        output[k++] = end_down;
        output[k++] = delete_down;
        output[k++] = delete_up;
        output[k++] = end_up;
        output[k++] = lshift_up;
    } else if (semicolonwait && (equal(input, &m_down) || equal(input, &m_repeat))) {
        output[k++] = enter_down;
        output[k++] = enter_up;
    } else if (semicolonwait && (equal(input, &n_down) || equal(input, &n_repeat))) {
        output[k++] = down_down;
        output[k++] = down_up;
    } else if (semicolonwait && (equal(input, &p_down) || equal(input, &p_repeat))) {
        output[k++] = up_down;
        output[k++] = up_up;
    } else if (semicolonwait && (equal(input, &u_down) || equal(input, &u_repeat))) {
        output[k++] = lshift_down;
        output[k++] = home_down;
        output[k++] = delete_down;
        output[k++] = delete_up;
        output[k++] = home_up;
        output[k++] = lshift_up;
    } else {
        if (capswait==1) {
            output[k++] = lctrl_down;
            capswait=0;
        }

        if (semicolonwait==1) {
            semicolonwait=2;
            if (altwait==1) {
                altwait=2;
            }
        }

        if (altwait==1) {
            output[k++] = lalt_down;
            dadd(lalt_down.code);
            altwait=0;
        }

        if (input->value == 2) {
            output[k++] = *input;
        } else if (input->value == 1) {
            output[k++] = *input;
            dadd(input->code);
        } else if (input->value == 0 && in_array(input->code)) {
            output[k++] = *input;
            dremove(input->code);
        }
    }

    return k;
}

int eventmap_loop(const char *devnode) {
    int result = 0;
    int fd = open(devnode, O_RDONLY);
    if (fd < 0)
        return 0;

    struct libevdev *dev;
    if (libevdev_new_from_fd(fd, &dev) < 0)
        goto teardown_fd;

    sleep(1);

    if (libevdev_grab(dev, LIBEVDEV_GRAB) < 0)
        goto teardown_dev;
    if (libevdev_enable_event_type(dev, EV_KEY) < 0)
        goto teardown_grab;
    if (libevdev_enable_event_code(dev, EV_KEY, KEY_ESC, NULL) < 0)
        goto teardown_grab;
    if (libevdev_enable_event_code(dev, EV_KEY, KEY_CAPSLOCK, NULL) < 0)
        goto teardown_grab;
    if (libevdev_enable_event_code(dev, EV_KEY, KEY_LEFTCTRL, NULL) < 0)
        goto teardown_grab;

    struct libevdev_uinput *udev;
    if (libevdev_uinput_create_from_device(dev, LIBEVDEV_UINPUT_OPEN_MANAGED,
                &udev) < 0)
        goto teardown_grab;

    struct state_s state = {.fsm = CAPS_UP, .key_up = &lctrl_up,
        .key_down = &lctrl_down, .last_input = {} };
    for (;;) {
        struct input_event input;
        int rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL |
                LIBEVDEV_READ_FLAG_BLOCKING, &input);

        while (rc == LIBEVDEV_READ_STATUS_SYNC)
            rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_SYNC, &input);

        if (rc == -EAGAIN)
            continue;

        if (rc != LIBEVDEV_READ_STATUS_SUCCESS)
            break;

        struct input_event output[6];
        for (int i = 0, k = eventmap(&input, output, &state); i < k; ++i)
            if (libevdev_uinput_write_event(udev, output[i].type, output[i].code,
                    output[i].value) < 0)
                goto teardown_udev;
    }

    result = 1;

teardown_udev:
    libevdev_uinput_destroy(udev);
teardown_grab:
    libevdev_grab(dev, LIBEVDEV_UNGRAB);
teardown_dev:
    libevdev_free(dev);
teardown_fd:
    close(fd);

    return result;
}

void eventmap_exec(const char *self_path, const char *devnode) {
    switch (fork()) {
    case -1:
        fprintf(stderr, "Fork failed on %s %s (%s)\n", self_path, devnode,
                strerror(errno));
        break;
    case 0: {
        char *command[] = {(char *)self_path, (char *)devnode, NULL};
        execvp(command[0], command);
        fprintf(stderr, "Exec failed on %s %s (%s)\n", self_path, devnode,
                strerror(errno));
    } break;
    }
}

int should_grab(struct udev_device *device, int initial_scan) {
    if (device == NULL)
        return 0;

    const char virtual_devices_directory[] = "/sys/devices/virtual/input/";
    if (strncmp(udev_device_get_syspath(device), virtual_devices_directory,
                sizeof(virtual_devices_directory) - 1) == 0)
        return 0;

    if (!initial_scan) {
        const char *action = udev_device_get_action(device);
        if (!action || strcmp(action, "add"))
            return 0;
    }

    const char input_prefix[] = "/dev/input/event";
    const char *devnode = udev_device_get_devnode(device);
    if (!devnode || strncmp(devnode, input_prefix, sizeof(input_prefix) - 1))
        return 0;

    int fd = open(devnode, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Failed to open %s (%s)\n", devnode, strerror(errno));
        return 0;
    }

    struct libevdev *dev;
    if (libevdev_new_from_fd(fd, &dev) < 0) {
        fprintf(stderr, "Failed to create evdev device from %s (%s)\n", devnode,
                strerror(errno));
        close(fd);
        return 0;
    }

    int should_be_grabbed =
        libevdev_has_event_type(dev, EV_KEY) &&
        (libevdev_has_event_code(dev, EV_KEY, KEY_ESC) ||
         libevdev_has_event_code(dev, EV_KEY, KEY_CAPSLOCK));

    libevdev_free(dev);
    close(fd);

    return should_be_grabbed;
}

void kill_zombies(__attribute__((unused)) int signum) {
    int status;
    while (waitpid(-1, &status, WNOHANG) > 0)
        ;
}

int main(int argc, const char *argv[]) {
    int initial_scan;

    if (argc > 2) {
        fprintf(stderr, "usage: caps2esc [device-path]\n");
        return EXIT_FAILURE;
    }

    if (argc == 2)
        return !eventmap_loop(argv[1]);

    struct sigaction sa;
    memset(&sa, 0, sizeof sa);
    sa.sa_flags = SA_NOCLDSTOP;
    sa.sa_handler = &kill_zombies;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("Couldn't summon zombie killer");
        return EXIT_FAILURE;
    }

    struct udev *udev = udev_new();
    if (!udev) {
        perror("Can't create udev");
        return EXIT_FAILURE;
    }

    struct udev_enumerate *enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "input");
    udev_enumerate_scan_devices(enumerate);
    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *dev_list_entry;
    udev_list_entry_foreach(dev_list_entry, devices) {
        struct udev_device *device = udev_device_new_from_syspath(
            udev, udev_list_entry_get_name(dev_list_entry));
        if (device) {
            if (should_grab(device, initial_scan = 1))
                eventmap_exec(argv[0], udev_device_get_devnode(device));
            udev_device_unref(device);
        }
    }
    udev_enumerate_unref(enumerate);

    struct udev_monitor *monitor = udev_monitor_new_from_netlink(udev, "udev");
    if (!monitor) {
        perror("Can't create monitor");
        return EXIT_FAILURE;
    }

    udev_monitor_filter_add_match_subsystem_devtype(monitor, "input", NULL);
    udev_monitor_enable_receiving(monitor);
    int fd = udev_monitor_get_fd(monitor);
    for (;;) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        if (select(fd + 1, &fds, NULL, NULL, NULL) > 0 && FD_ISSET(fd, &fds)) {
            struct udev_device *device = udev_monitor_receive_device(monitor);
            if (device) {
                if (should_grab(device, initial_scan = 0))
                    eventmap_exec(argv[0], udev_device_get_devnode(device));
                udev_device_unref(device);
            }
        }
    }

    udev_monitor_unref(monitor);
    udev_unref(udev);
}
