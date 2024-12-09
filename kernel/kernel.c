/**
 * -------------------------------------------------------------------------
 *                                   AurorOS
 * (c) 2022-2024 Interpuce
 * 
 * You should receive AurorOS license with this source code. If not - check:
 *  https://github.com/Interpuce/AurorOS/blob/main/LICENSE.md
 * -------------------------------------------------------------------------
 */

#include "kernel.h"

#include <string.h>
#include <msg.h>
#include <panic.h>
#include <types.h>
#include <input.h>
#include <constants.h>
#include <asm/power.h>

#include "commands/commands.h"

void main() {
    clearscreen();

    uint16_t permlvl = 4;
    uint16_t betaState = 1;
    string current_user = "root";

    if (betaState == 1) {
        print_warn("You are running early build of AurorOS!");
    }
        

    char buffer[128];
    char *args[10];
    while (1) {
        printprefix(current_user, PC_NAME);
        read_str(buffer, sizeof(buffer), 0, 0x07);

        int arg_count = split_str(buffer, ' ', args, 10);

        if (arg_count > 0) {
            char farg[1024] = "";
            for (int i = 1; i < arg_count; i++) {
                strcat(farg, args[i]);
                strcat(farg, " ");
            }

            if (streql(args[0], "ver")) {
                print(AUROR_NAME, 0x07);
                print();
                println(AUROR_VERSION, 0x07);
            } else if (streql(args[0], "print")) {
                println(farg ,0x07);
            } else if (streql(args[0], "cowsay")) {
                cowsay(farg);
            } else if (streql(args[0], "map")) {
                map();
            } else if (streql(args[0], "clear")) {
                clearscreen();
            } else if (streql(args[0], "reboot")) {
                reboot();
            } else if (streql(args[0], "shutdown")) {
                shutdown();
            } else {
                print_error("Invalid command!");
            }
        }
    }

    kernelpanic("KERNEL_MAIN_LOOP_EXITED");
}
