from __future__ import annotations

from .constant import Constant

__NR_exit = Constant("__NR_exit", 1)
__NR_fork = Constant("__NR_fork", 2)
__NR_read = Constant("__NR_read", 3)
__NR_write = Constant("__NR_write", 4)
__NR_open = Constant("__NR_open", 5)
__NR_close = Constant("__NR_close", 6)
__NR_creat = Constant("__NR_creat", 8)
__NR_link = Constant("__NR_link", 9)
__NR_unlink = Constant("__NR_unlink", 10)
__NR_execve = Constant("__NR_execve", 11)
__NR_chdir = Constant("__NR_chdir", 12)
__NR_time = Constant("__NR_time", 13)
__NR_mknod = Constant("__NR_mknod", 14)
__NR_chmod = Constant("__NR_chmod", 15)
__NR_lchown = Constant("__NR_lchown", 16)
__NR_lseek = Constant("__NR_lseek", 19)
__NR_getpid = Constant("__NR_getpid", 20)
__NR_mount = Constant("__NR_mount", 21)
__NR_umount = Constant("__NR_umount", 22)
__NR_setuid = Constant("__NR_setuid", 23)
__NR_getuid = Constant("__NR_getuid", 24)
__NR_stime = Constant("__NR_stime", 25)
__NR_ptrace = Constant("__NR_ptrace", 26)
__NR_alarm = Constant("__NR_alarm", 27)
__NR_pause = Constant("__NR_pause", 29)
__NR_utime = Constant("__NR_utime", 30)
__NR_access = Constant("__NR_access", 33)
__NR_nice = Constant("__NR_nice", 34)
__NR_sync = Constant("__NR_sync", 36)
__NR_kill = Constant("__NR_kill", 37)
__NR_rename = Constant("__NR_rename", 38)
__NR_mkdir = Constant("__NR_mkdir", 39)
__NR_rmdir = Constant("__NR_rmdir", 40)
__NR_dup = Constant("__NR_dup", 41)
__NR_pipe = Constant("__NR_pipe", 42)
__NR_times = Constant("__NR_times", 43)
__NR_brk = Constant("__NR_brk", 45)
__NR_setgid = Constant("__NR_setgid", 46)
__NR_getgid = Constant("__NR_getgid", 47)
__NR_signal = Constant("__NR_signal", 48)
__NR_geteuid = Constant("__NR_geteuid", 49)
__NR_getegid = Constant("__NR_getegid", 50)
__NR_acct = Constant("__NR_acct", 51)
__NR_umount2 = Constant("__NR_umount2", 52)
__NR_ioctl = Constant("__NR_ioctl", 54)
__NR_fcntl = Constant("__NR_fcntl", 55)
__NR_setpgid = Constant("__NR_setpgid", 57)
__NR_umask = Constant("__NR_umask", 60)
__NR_chroot = Constant("__NR_chroot", 61)
__NR_ustat = Constant("__NR_ustat", 62)
__NR_dup2 = Constant("__NR_dup2", 63)
__NR_getppid = Constant("__NR_getppid", 64)
__NR_getpgrp = Constant("__NR_getpgrp", 65)
__NR_setsid = Constant("__NR_setsid", 66)
__NR_sigaction = Constant("__NR_sigaction", 67)
__NR_setreuid = Constant("__NR_setreuid", 70)
__NR_setregid = Constant("__NR_setregid", 71)
__NR_sigsuspend = Constant("__NR_sigsuspend", 72)
__NR_sigpending = Constant("__NR_sigpending", 73)
__NR_sethostname = Constant("__NR_sethostname", 74)
__NR_setrlimit = Constant("__NR_setrlimit", 75)
__NR_getrlimit = Constant("__NR_getrlimit", 76)
__NR_getrusage = Constant("__NR_getrusage", 77)
__NR_gettimeofday = Constant("__NR_gettimeofday", 78)
__NR_settimeofday = Constant("__NR_settimeofday", 79)
__NR_getgroups = Constant("__NR_getgroups", 80)
__NR_setgroups = Constant("__NR_setgroups", 81)
__NR_symlink = Constant("__NR_symlink", 83)
__NR_readlink = Constant("__NR_readlink", 85)
__NR_uselib = Constant("__NR_uselib", 86)
__NR_swapon = Constant("__NR_swapon", 87)
__NR_reboot = Constant("__NR_reboot", 88)
__NR_readdir = Constant("__NR_readdir", 89)
__NR_mmap = Constant("__NR_mmap", 90)
__NR_munmap = Constant("__NR_munmap", 91)
__NR_truncate = Constant("__NR_truncate", 92)
__NR_ftruncate = Constant("__NR_ftruncate", 93)
__NR_fchmod = Constant("__NR_fchmod", 94)
__NR_fchown = Constant("__NR_fchown", 95)
__NR_getpriority = Constant("__NR_getpriority", 96)
__NR_setpriority = Constant("__NR_setpriority", 97)
__NR_statfs = Constant("__NR_statfs", 99)
__NR_fstatfs = Constant("__NR_fstatfs", 100)
__NR_ioperm = Constant("__NR_ioperm", 101)
__NR_socketcall = Constant("__NR_socketcall", 102)
__NR_syslog = Constant("__NR_syslog", 103)
__NR_setitimer = Constant("__NR_setitimer", 104)
__NR_getitimer = Constant("__NR_getitimer", 105)
__NR_stat = Constant("__NR_stat", 106)
__NR_lstat = Constant("__NR_lstat", 107)
__NR_fstat = Constant("__NR_fstat", 108)
__NR_lookup_dcookie = Constant("__NR_lookup_dcookie", 110)
__NR_vhangup = Constant("__NR_vhangup", 111)
__NR_idle = Constant("__NR_idle", 112)
__NR_wait4 = Constant("__NR_wait4", 114)
__NR_swapoff = Constant("__NR_swapoff", 115)
__NR_sysinfo = Constant("__NR_sysinfo", 116)
__NR_ipc = Constant("__NR_ipc", 117)
__NR_fsync = Constant("__NR_fsync", 118)
__NR_sigreturn = Constant("__NR_sigreturn", 119)
__NR_clone = Constant("__NR_clone", 120)
__NR_setdomainname = Constant("__NR_setdomainname", 121)
__NR_uname = Constant("__NR_uname", 122)
__NR_adjtimex = Constant("__NR_adjtimex", 124)
__NR_mprotect = Constant("__NR_mprotect", 125)
__NR_sigprocmask = Constant("__NR_sigprocmask", 126)
__NR_create_module = Constant("__NR_create_module", 127)
__NR_init_module = Constant("__NR_init_module", 128)
__NR_delete_module = Constant("__NR_delete_module", 129)
__NR_get_kernel_syms = Constant("__NR_get_kernel_syms", 130)
__NR_quotactl = Constant("__NR_quotactl", 131)
__NR_getpgid = Constant("__NR_getpgid", 132)
__NR_fchdir = Constant("__NR_fchdir", 133)
__NR_bdflush = Constant("__NR_bdflush", 134)
__NR_sysfs = Constant("__NR_sysfs", 135)
__NR_personality = Constant("__NR_personality", 136)
__NR_afs_syscall = Constant("__NR_afs_syscall", 137)
__NR_setfsuid = Constant("__NR_setfsuid", 138)
__NR_setfsgid = Constant("__NR_setfsgid", 139)
__NR__llseek = Constant("__NR__llseek", 140)
__NR_getdents = Constant("__NR_getdents", 141)
__NR__newselect = Constant("__NR__newselect", 142)
__NR_flock = Constant("__NR_flock", 143)
__NR_msync = Constant("__NR_msync", 144)
__NR_readv = Constant("__NR_readv", 145)
__NR_writev = Constant("__NR_writev", 146)
__NR_getsid = Constant("__NR_getsid", 147)
__NR_fdatasync = Constant("__NR_fdatasync", 148)
__NR__sysctl = Constant("__NR__sysctl", 149)
__NR_mlock = Constant("__NR_mlock", 150)
__NR_munlock = Constant("__NR_munlock", 151)
__NR_mlockall = Constant("__NR_mlockall", 152)
__NR_munlockall = Constant("__NR_munlockall", 153)
__NR_sched_setparam = Constant("__NR_sched_setparam", 154)
__NR_sched_getparam = Constant("__NR_sched_getparam", 155)
__NR_sched_setscheduler = Constant("__NR_sched_setscheduler", 156)
__NR_sched_getscheduler = Constant("__NR_sched_getscheduler", 157)
__NR_sched_yield = Constant("__NR_sched_yield", 158)
__NR_sched_get_priority_max = Constant("__NR_sched_get_priority_max", 159)
__NR_sched_get_priority_min = Constant("__NR_sched_get_priority_min", 160)
__NR_sched_rr_get_interval = Constant("__NR_sched_rr_get_interval", 161)
__NR_nanosleep = Constant("__NR_nanosleep", 162)
__NR_mremap = Constant("__NR_mremap", 163)
__NR_setresuid = Constant("__NR_setresuid", 164)
__NR_getresuid = Constant("__NR_getresuid", 165)
__NR_query_module = Constant("__NR_query_module", 167)
__NR_poll = Constant("__NR_poll", 168)
__NR_nfsservctl = Constant("__NR_nfsservctl", 169)
__NR_setresgid = Constant("__NR_setresgid", 170)
__NR_getresgid = Constant("__NR_getresgid", 171)
__NR_prctl = Constant("__NR_prctl", 172)
__NR_rt_sigreturn = Constant("__NR_rt_sigreturn", 173)
__NR_rt_sigaction = Constant("__NR_rt_sigaction", 174)
__NR_rt_sigprocmask = Constant("__NR_rt_sigprocmask", 175)
__NR_rt_sigpending = Constant("__NR_rt_sigpending", 176)
__NR_rt_sigtimedwait = Constant("__NR_rt_sigtimedwait", 177)
__NR_rt_sigqueueinfo = Constant("__NR_rt_sigqueueinfo", 178)
__NR_rt_sigsuspend = Constant("__NR_rt_sigsuspend", 179)
__NR_pread = Constant("__NR_pread", 180)
__NR_pwrite = Constant("__NR_pwrite", 181)
__NR_chown = Constant("__NR_chown", 182)
__NR_getcwd = Constant("__NR_getcwd", 183)
__NR_capget = Constant("__NR_capget", 184)
__NR_capset = Constant("__NR_capset", 185)
__NR_sigaltstack = Constant("__NR_sigaltstack", 186)
__NR_sendfile = Constant("__NR_sendfile", 187)
__NR_getpmsg = Constant("__NR_getpmsg", 188)
__NR_putpmsg = Constant("__NR_putpmsg", 189)
__NR_vfork = Constant("__NR_vfork", 190)
__NR_ugetrlimit = Constant("__NR_ugetrlimit", 191)
__NR_mmap2 = Constant("__NR_mmap2", 192)
__NR_truncate64 = Constant("__NR_truncate64", 193)
__NR_ftruncate64 = Constant("__NR_ftruncate64", 194)
__NR_stat64 = Constant("__NR_stat64", 195)
__NR_lstat64 = Constant("__NR_lstat64", 196)
__NR_fstat64 = Constant("__NR_fstat64", 197)
__NR_lchown32 = Constant("__NR_lchown32", 198)
__NR_getuid32 = Constant("__NR_getuid32", 199)
__NR_getgid32 = Constant("__NR_getgid32", 200)
__NR_geteuid32 = Constant("__NR_geteuid32", 201)
__NR_getegid32 = Constant("__NR_getegid32", 202)
__NR_setreuid32 = Constant("__NR_setreuid32", 203)
__NR_setregid32 = Constant("__NR_setregid32", 204)
__NR_getgroups32 = Constant("__NR_getgroups32", 205)
__NR_setgroups32 = Constant("__NR_setgroups32", 206)
__NR_fchown32 = Constant("__NR_fchown32", 207)
__NR_setresuid32 = Constant("__NR_setresuid32", 208)
__NR_getresuid32 = Constant("__NR_getresuid32", 209)
__NR_setresgid32 = Constant("__NR_setresgid32", 210)
__NR_getresgid32 = Constant("__NR_getresgid32", 211)
__NR_chown32 = Constant("__NR_chown32", 212)
__NR_setuid32 = Constant("__NR_setuid32", 213)
__NR_setgid32 = Constant("__NR_setgid32", 214)
__NR_setfsuid32 = Constant("__NR_setfsuid32", 215)
__NR_setfsgid32 = Constant("__NR_setfsgid32", 216)
__NR_pivot_root = Constant("__NR_pivot_root", 217)
__NR_mincore = Constant("__NR_mincore", 218)
__NR_madvise = Constant("__NR_madvise", 219)
__NR_getdents64 = Constant("__NR_getdents64", 220)
__NR_fcntl64 = Constant("__NR_fcntl64", 221)
__NR_readahead = Constant("__NR_readahead", 222)
__NR_sendfile64 = Constant("__NR_sendfile64", 223)
__NR_setxattr = Constant("__NR_setxattr", 224)
__NR_lsetxattr = Constant("__NR_lsetxattr", 225)
__NR_fsetxattr = Constant("__NR_fsetxattr", 226)
__NR_getxattr = Constant("__NR_getxattr", 227)
__NR_lgetxattr = Constant("__NR_lgetxattr", 228)
__NR_fgetxattr = Constant("__NR_fgetxattr", 229)
__NR_listxattr = Constant("__NR_listxattr", 230)
__NR_llistxattr = Constant("__NR_llistxattr", 231)
__NR_flistxattr = Constant("__NR_flistxattr", 232)
__NR_removexattr = Constant("__NR_removexattr", 233)
__NR_lremovexattr = Constant("__NR_lremovexattr", 234)
__NR_fremovexattr = Constant("__NR_fremovexattr", 235)
__NR_gettid = Constant("__NR_gettid", 236)
__NR_tkill = Constant("__NR_tkill", 237)
__NR_futex = Constant("__NR_futex", 238)
__NR_sched_setaffinity = Constant("__NR_sched_setaffinity", 239)
__NR_sched_getaffinity = Constant("__NR_sched_getaffinity", 240)
__NR_tgkill = Constant("__NR_tgkill", 241)
__NR_io_setup = Constant("__NR_io_setup", 243)
__NR_io_destroy = Constant("__NR_io_destroy", 244)
__NR_io_getevents = Constant("__NR_io_getevents", 245)
__NR_io_submit = Constant("__NR_io_submit", 246)
__NR_io_cancel = Constant("__NR_io_cancel", 247)
__NR_exit_group = Constant("__NR_exit_group", 248)
__NR_epoll_create = Constant("__NR_epoll_create", 249)
__NR_epoll_ctl = Constant("__NR_epoll_ctl", 250)
__NR_epoll_wait = Constant("__NR_epoll_wait", 251)
__NR_set_tid_address = Constant("__NR_set_tid_address", 252)
__NR_fadvise64 = Constant("__NR_fadvise64", 253)
__NR_timer_create = Constant("__NR_timer_create", 254)
__NR_timer_settime = Constant("__NR_timer_settime", (254 + 1))
__NR_timer_gettime = Constant("__NR_timer_gettime", (254 + 2))
__NR_timer_getoverrun = Constant("__NR_timer_getoverrun", (254 + 3))
__NR_timer_delete = Constant("__NR_timer_delete", (254 + 4))
__NR_clock_settime = Constant("__NR_clock_settime", (254 + 5))
__NR_clock_gettime = Constant("__NR_clock_gettime", (254 + 6))
__NR_clock_getres = Constant("__NR_clock_getres", (254 + 7))
__NR_clock_nanosleep = Constant("__NR_clock_nanosleep", (254 + 8))
__NR_fadvise64_64 = Constant("__NR_fadvise64_64", 264)
__NR_statfs64 = Constant("__NR_statfs64", 265)
__NR_fstatfs64 = Constant("__NR_fstatfs64", 266)
__NR_remap_file_pages = Constant("__NR_remap_file_pages", 267)
__NR_mq_open = Constant("__NR_mq_open", 271)
__NR_mq_unlink = Constant("__NR_mq_unlink", 272)
__NR_mq_timedsend = Constant("__NR_mq_timedsend", 273)
__NR_mq_timedreceive = Constant("__NR_mq_timedreceive", 274)
__NR_mq_notify = Constant("__NR_mq_notify", 275)
__NR_mq_getsetattr = Constant("__NR_mq_getsetattr", 276)
__NR_kexec_load = Constant("__NR_kexec_load", 277)
__NR_add_key = Constant("__NR_add_key", 278)
__NR_request_key = Constant("__NR_request_key", 279)
__NR_keyctl = Constant("__NR_keyctl", 280)
__NR_waitid = Constant("__NR_waitid", 281)
__NR_ioprio_set = Constant("__NR_ioprio_set", 282)
__NR_ioprio_get = Constant("__NR_ioprio_get", 283)
__NR_inotify_init = Constant("__NR_inotify_init", 284)
__NR_inotify_add_watch = Constant("__NR_inotify_add_watch", 285)
__NR_inotify_rm_watch = Constant("__NR_inotify_rm_watch", 286)
__NR_openat = Constant("__NR_openat", 288)
__NR_mkdirat = Constant("__NR_mkdirat", 289)
__NR_mknodat = Constant("__NR_mknodat", 290)
__NR_fchownat = Constant("__NR_fchownat", 291)
__NR_futimesat = Constant("__NR_futimesat", 292)
__NR_unlinkat = Constant("__NR_unlinkat", 294)
__NR_renameat = Constant("__NR_renameat", 295)
__NR_linkat = Constant("__NR_linkat", 296)
__NR_symlinkat = Constant("__NR_symlinkat", 297)
__NR_readlinkat = Constant("__NR_readlinkat", 298)
__NR_fchmodat = Constant("__NR_fchmodat", 299)
__NR_faccessat = Constant("__NR_faccessat", 300)
__NR_pselect6 = Constant("__NR_pselect6", 301)
__NR_ppoll = Constant("__NR_ppoll", 302)
__NR_unshare = Constant("__NR_unshare", 303)
__NR_set_robust_list = Constant("__NR_set_robust_list", 304)
__NR_get_robust_list = Constant("__NR_get_robust_list", 305)
__NR_splice = Constant("__NR_splice", 306)
__NR_sync_file_range = Constant("__NR_sync_file_range", 307)
__NR_tee = Constant("__NR_tee", 308)
__NR_vmsplice = Constant("__NR_vmsplice", 309)
__NR_getcpu = Constant("__NR_getcpu", 311)
__NR_epoll_pwait = Constant("__NR_epoll_pwait", 312)
__NR_utimes = Constant("__NR_utimes", 313)
__NR_fallocate = Constant("__NR_fallocate", 314)
__NR_utimensat = Constant("__NR_utimensat", 315)
__NR_signalfd = Constant("__NR_signalfd", 316)
__NR_timerfd = Constant("__NR_timerfd", 317)
__NR_eventfd = Constant("__NR_eventfd", 318)
__NR_timerfd_create = Constant("__NR_timerfd_create", 319)
__NR_timerfd_settime = Constant("__NR_timerfd_settime", 320)
__NR_timerfd_gettime = Constant("__NR_timerfd_gettime", 321)
__SYS_NERR = Constant("__SYS_NERR", ((129) + 1))
_SYS_TIME_H = Constant("_SYS_TIME_H", 1)
SYS_access = Constant("SYS_access", 33)
SYS_acct = Constant("SYS_acct", 51)
SYS_add_key = Constant("SYS_add_key", 278)
SYS_adjtimex = Constant("SYS_adjtimex", 124)
SYS_afs_syscall = Constant("SYS_afs_syscall", 137)
SYS_alarm = Constant("SYS_alarm", 27)
SYS_bdflush = Constant("SYS_bdflush", 134)
SYS_brk = Constant("SYS_brk", 45)
SYS_capget = Constant("SYS_capget", 184)
SYS_capset = Constant("SYS_capset", 185)
SYS_chdir = Constant("SYS_chdir", 12)
SYS_chmod = Constant("SYS_chmod", 15)
SYS_chown = Constant("SYS_chown", 182)
SYS_chown32 = Constant("SYS_chown32", 212)
SYS_chroot = Constant("SYS_chroot", 61)
SYS_clock_getres = Constant("SYS_clock_getres", (254 + 7))
SYS_clock_gettime = Constant("SYS_clock_gettime", (254 + 6))
SYS_clock_nanosleep = Constant("SYS_clock_nanosleep", (254 + 8))
SYS_clock_settime = Constant("SYS_clock_settime", (254 + 5))
SYS_clone = Constant("SYS_clone", 120)
SYS_close = Constant("SYS_close", 6)
SYS_creat = Constant("SYS_creat", 8)
SYS_create_module = Constant("SYS_create_module", 127)
SYS_delete_module = Constant("SYS_delete_module", 129)
SYS_dup = Constant("SYS_dup", 41)
SYS_dup2 = Constant("SYS_dup2", 63)
SYS_epoll_create = Constant("SYS_epoll_create", 249)
SYS_epoll_ctl = Constant("SYS_epoll_ctl", 250)
SYS_epoll_pwait = Constant("SYS_epoll_pwait", 312)
SYS_epoll_wait = Constant("SYS_epoll_wait", 251)
SYS_eventfd = Constant("SYS_eventfd", 318)
SYS_execve = Constant("SYS_execve", 11)
SYS_exit = Constant("SYS_exit", 1)
SYS_exit_group = Constant("SYS_exit_group", 248)
SYS_faccessat = Constant("SYS_faccessat", 300)
SYS_fadvise64 = Constant("SYS_fadvise64", 253)
SYS_fadvise64_64 = Constant("SYS_fadvise64_64", 264)
SYS_fallocate = Constant("SYS_fallocate", 314)
SYS_fchdir = Constant("SYS_fchdir", 133)
SYS_fchmod = Constant("SYS_fchmod", 94)
SYS_fchmodat = Constant("SYS_fchmodat", 299)
SYS_fchown = Constant("SYS_fchown", 95)
SYS_fchown32 = Constant("SYS_fchown32", 207)
SYS_fchownat = Constant("SYS_fchownat", 291)
SYS_fcntl = Constant("SYS_fcntl", 55)
SYS_fcntl64 = Constant("SYS_fcntl64", 221)
SYS_fdatasync = Constant("SYS_fdatasync", 148)
SYS_fgetxattr = Constant("SYS_fgetxattr", 229)
SYS_flistxattr = Constant("SYS_flistxattr", 232)
SYS_flock = Constant("SYS_flock", 143)
SYS_fork = Constant("SYS_fork", 2)
SYS_fremovexattr = Constant("SYS_fremovexattr", 235)
SYS_fsetxattr = Constant("SYS_fsetxattr", 226)
SYS_fstat = Constant("SYS_fstat", 108)
SYS_fstat64 = Constant("SYS_fstat64", 197)
SYS_fstatfs = Constant("SYS_fstatfs", 100)
SYS_fstatfs64 = Constant("SYS_fstatfs64", 266)
SYS_fsync = Constant("SYS_fsync", 118)
SYS_ftruncate = Constant("SYS_ftruncate", 93)
SYS_ftruncate64 = Constant("SYS_ftruncate64", 194)
SYS_futex = Constant("SYS_futex", 238)
SYS_futimesat = Constant("SYS_futimesat", 292)
SYS_getcpu = Constant("SYS_getcpu", 311)
SYS_getcwd = Constant("SYS_getcwd", 183)
SYS_getdents = Constant("SYS_getdents", 141)
SYS_getdents64 = Constant("SYS_getdents64", 220)
SYS_getegid = Constant("SYS_getegid", 50)
SYS_getegid32 = Constant("SYS_getegid32", 202)
SYS_geteuid = Constant("SYS_geteuid", 49)
SYS_geteuid32 = Constant("SYS_geteuid32", 201)
SYS_getgid = Constant("SYS_getgid", 47)
SYS_getgid32 = Constant("SYS_getgid32", 200)
SYS_getgroups = Constant("SYS_getgroups", 80)
SYS_getgroups32 = Constant("SYS_getgroups32", 205)
SYS_getitimer = Constant("SYS_getitimer", 105)
SYS_get_kernel_syms = Constant("SYS_get_kernel_syms", 130)
SYS_getpgid = Constant("SYS_getpgid", 132)
SYS_getpgrp = Constant("SYS_getpgrp", 65)
SYS_getpid = Constant("SYS_getpid", 20)
SYS_getpmsg = Constant("SYS_getpmsg", 188)
SYS_getppid = Constant("SYS_getppid", 64)
SYS_getpriority = Constant("SYS_getpriority", 96)
SYS_getresgid = Constant("SYS_getresgid", 171)
SYS_getresgid32 = Constant("SYS_getresgid32", 211)
SYS_getresuid = Constant("SYS_getresuid", 165)
SYS_getresuid32 = Constant("SYS_getresuid32", 209)
SYS_getrlimit = Constant("SYS_getrlimit", 76)
SYS_get_robust_list = Constant("SYS_get_robust_list", 305)
SYS_getrusage = Constant("SYS_getrusage", 77)
SYS_getsid = Constant("SYS_getsid", 147)
SYS_gettid = Constant("SYS_gettid", 236)
SYS_gettimeofday = Constant("SYS_gettimeofday", 78)
SYS_getuid = Constant("SYS_getuid", 24)
SYS_getuid32 = Constant("SYS_getuid32", 199)
SYS_getxattr = Constant("SYS_getxattr", 227)
SYS_idle = Constant("SYS_idle", 112)
SYS_init_module = Constant("SYS_init_module", 128)
SYS_inotify_add_watch = Constant("SYS_inotify_add_watch", 285)
SYS_inotify_init = Constant("SYS_inotify_init", 284)
SYS_inotify_rm_watch = Constant("SYS_inotify_rm_watch", 286)
SYS_io_cancel = Constant("SYS_io_cancel", 247)
SYS_ioctl = Constant("SYS_ioctl", 54)
SYS_io_destroy = Constant("SYS_io_destroy", 244)
SYS_io_getevents = Constant("SYS_io_getevents", 245)
SYS_ioperm = Constant("SYS_ioperm", 101)
SYS_ioprio_get = Constant("SYS_ioprio_get", 283)
SYS_ioprio_set = Constant("SYS_ioprio_set", 282)
SYS_io_setup = Constant("SYS_io_setup", 243)
SYS_io_submit = Constant("SYS_io_submit", 246)
SYS_ipc = Constant("SYS_ipc", 117)
SYS_kexec_load = Constant("SYS_kexec_load", 277)
SYS_keyctl = Constant("SYS_keyctl", 280)
SYS_kill = Constant("SYS_kill", 37)
SYS_lchown = Constant("SYS_lchown", 16)
SYS_lchown32 = Constant("SYS_lchown32", 198)
SYS_lgetxattr = Constant("SYS_lgetxattr", 228)
SYS_link = Constant("SYS_link", 9)
SYS_linkat = Constant("SYS_linkat", 296)
SYS_listxattr = Constant("SYS_listxattr", 230)
SYS_llistxattr = Constant("SYS_llistxattr", 231)
SYS__llseek = Constant("SYS__llseek", 140)
SYS_lookup_dcookie = Constant("SYS_lookup_dcookie", 110)
SYS_lremovexattr = Constant("SYS_lremovexattr", 234)
SYS_lseek = Constant("SYS_lseek", 19)
SYS_lsetxattr = Constant("SYS_lsetxattr", 225)
SYS_lstat = Constant("SYS_lstat", 107)
SYS_lstat64 = Constant("SYS_lstat64", 196)
SYS_madvise = Constant("SYS_madvise", 219)
SYS_mincore = Constant("SYS_mincore", 218)
SYS_mkdir = Constant("SYS_mkdir", 39)
SYS_mkdirat = Constant("SYS_mkdirat", 289)
SYS_mknod = Constant("SYS_mknod", 14)
SYS_mknodat = Constant("SYS_mknodat", 290)
SYS_mlock = Constant("SYS_mlock", 150)
SYS_mlockall = Constant("SYS_mlockall", 152)
SYS_mmap = Constant("SYS_mmap", 90)
SYS_mmap2 = Constant("SYS_mmap2", 192)
SYS_mount = Constant("SYS_mount", 21)
SYS_mprotect = Constant("SYS_mprotect", 125)
SYS_mq_getsetattr = Constant("SYS_mq_getsetattr", 276)
SYS_mq_notify = Constant("SYS_mq_notify", 275)
SYS_mq_open = Constant("SYS_mq_open", 271)
SYS_mq_timedreceive = Constant("SYS_mq_timedreceive", 274)
SYS_mq_timedsend = Constant("SYS_mq_timedsend", 273)
SYS_mq_unlink = Constant("SYS_mq_unlink", 272)
SYS_mremap = Constant("SYS_mremap", 163)
SYS_msync = Constant("SYS_msync", 144)
SYS_munlock = Constant("SYS_munlock", 151)
SYS_munlockall = Constant("SYS_munlockall", 153)
SYS_munmap = Constant("SYS_munmap", 91)
SYS_nanosleep = Constant("SYS_nanosleep", 162)
SYS__newselect = Constant("SYS__newselect", 142)
SYS_nfsservctl = Constant("SYS_nfsservctl", 169)
SYS_nice = Constant("SYS_nice", 34)
SYS_open = Constant("SYS_open", 5)
SYS_openat = Constant("SYS_openat", 288)
SYS_pause = Constant("SYS_pause", 29)
SYS_personality = Constant("SYS_personality", 136)
SYS_pipe = Constant("SYS_pipe", 42)
SYS_pivot_root = Constant("SYS_pivot_root", 217)
SYS_poll = Constant("SYS_poll", 168)
SYS_ppoll = Constant("SYS_ppoll", 302)
SYS_prctl = Constant("SYS_prctl", 172)
SYS_pread = Constant("SYS_pread", 180)
SYS_pselect6 = Constant("SYS_pselect6", 301)
SYS_ptrace = Constant("SYS_ptrace", 26)
SYS_putpmsg = Constant("SYS_putpmsg", 189)
SYS_pwrite = Constant("SYS_pwrite", 181)
SYS_query_module = Constant("SYS_query_module", 167)
SYS_quotactl = Constant("SYS_quotactl", 131)
SYS_read = Constant("SYS_read", 3)
SYS_readahead = Constant("SYS_readahead", 222)
SYS_readdir = Constant("SYS_readdir", 89)
SYS_readlink = Constant("SYS_readlink", 85)
SYS_readlinkat = Constant("SYS_readlinkat", 298)
SYS_readv = Constant("SYS_readv", 145)
SYS_reboot = Constant("SYS_reboot", 88)
SYS_remap_file_pages = Constant("SYS_remap_file_pages", 267)
SYS_removexattr = Constant("SYS_removexattr", 233)
SYS_rename = Constant("SYS_rename", 38)
SYS_renameat = Constant("SYS_renameat", 295)
SYS_request_key = Constant("SYS_request_key", 279)
SYS_rmdir = Constant("SYS_rmdir", 40)
SYS_rt_sigaction = Constant("SYS_rt_sigaction", 174)
SYS_rt_sigpending = Constant("SYS_rt_sigpending", 176)
SYS_rt_sigprocmask = Constant("SYS_rt_sigprocmask", 175)
SYS_rt_sigqueueinfo = Constant("SYS_rt_sigqueueinfo", 178)
SYS_rt_sigreturn = Constant("SYS_rt_sigreturn", 173)
SYS_rt_sigsuspend = Constant("SYS_rt_sigsuspend", 179)
SYS_rt_sigtimedwait = Constant("SYS_rt_sigtimedwait", 177)
SYS_sched_getaffinity = Constant("SYS_sched_getaffinity", 240)
SYS_sched_getparam = Constant("SYS_sched_getparam", 155)
SYS_sched_get_priority_max = Constant("SYS_sched_get_priority_max", 159)
SYS_sched_get_priority_min = Constant("SYS_sched_get_priority_min", 160)
SYS_sched_getscheduler = Constant("SYS_sched_getscheduler", 157)
SYS_sched_rr_get_interval = Constant("SYS_sched_rr_get_interval", 161)
SYS_sched_setaffinity = Constant("SYS_sched_setaffinity", 239)
SYS_sched_setparam = Constant("SYS_sched_setparam", 154)
SYS_sched_setscheduler = Constant("SYS_sched_setscheduler", 156)
SYS_sched_yield = Constant("SYS_sched_yield", 158)
SYS_sendfile = Constant("SYS_sendfile", 187)
SYS_sendfile64 = Constant("SYS_sendfile64", 223)
SYS_setdomainname = Constant("SYS_setdomainname", 121)
SYS_setfsgid = Constant("SYS_setfsgid", 139)
SYS_setfsgid32 = Constant("SYS_setfsgid32", 216)
SYS_setfsuid = Constant("SYS_setfsuid", 138)
SYS_setfsuid32 = Constant("SYS_setfsuid32", 215)
SYS_setgid = Constant("SYS_setgid", 46)
SYS_setgid32 = Constant("SYS_setgid32", 214)
SYS_setgroups = Constant("SYS_setgroups", 81)
SYS_setgroups32 = Constant("SYS_setgroups32", 206)
SYS_sethostname = Constant("SYS_sethostname", 74)
SYS_setitimer = Constant("SYS_setitimer", 104)
SYS_setpgid = Constant("SYS_setpgid", 57)
SYS_setpriority = Constant("SYS_setpriority", 97)
SYS_setregid = Constant("SYS_setregid", 71)
SYS_setregid32 = Constant("SYS_setregid32", 204)
SYS_setresgid = Constant("SYS_setresgid", 170)
SYS_setresgid32 = Constant("SYS_setresgid32", 210)
SYS_setresuid = Constant("SYS_setresuid", 164)
SYS_setresuid32 = Constant("SYS_setresuid32", 208)
SYS_setreuid = Constant("SYS_setreuid", 70)
SYS_setreuid32 = Constant("SYS_setreuid32", 203)
SYS_setrlimit = Constant("SYS_setrlimit", 75)
SYS_set_robust_list = Constant("SYS_set_robust_list", 304)
SYS_setsid = Constant("SYS_setsid", 66)
SYS_set_tid_address = Constant("SYS_set_tid_address", 252)
SYS_settimeofday = Constant("SYS_settimeofday", 79)
SYS_setuid = Constant("SYS_setuid", 23)
SYS_setuid32 = Constant("SYS_setuid32", 213)
SYS_setxattr = Constant("SYS_setxattr", 224)
SYS_sigaction = Constant("SYS_sigaction", 67)
SYS_sigaltstack = Constant("SYS_sigaltstack", 186)
SYS_signal = Constant("SYS_signal", 48)
SYS_signalfd = Constant("SYS_signalfd", 316)
SYS_sigpending = Constant("SYS_sigpending", 73)
SYS_sigprocmask = Constant("SYS_sigprocmask", 126)
SYS_sigreturn = Constant("SYS_sigreturn", 119)
SYS_sigsuspend = Constant("SYS_sigsuspend", 72)
SYS_socketcall = Constant("SYS_socketcall", 102)
SYS_splice = Constant("SYS_splice", 306)
SYS_stat = Constant("SYS_stat", 106)
SYS_stat64 = Constant("SYS_stat64", 195)
SYS_statfs = Constant("SYS_statfs", 99)
SYS_statfs64 = Constant("SYS_statfs64", 265)
SYS_stime = Constant("SYS_stime", 25)
SYS_swapoff = Constant("SYS_swapoff", 115)
SYS_swapon = Constant("SYS_swapon", 87)
SYS_symlink = Constant("SYS_symlink", 83)
SYS_symlinkat = Constant("SYS_symlinkat", 297)
SYS_sync = Constant("SYS_sync", 36)
SYS_sync_file_range = Constant("SYS_sync_file_range", 307)
SYS__sysctl = Constant("SYS__sysctl", 149)
SYS_sysfs = Constant("SYS_sysfs", 135)
SYS_sysinfo = Constant("SYS_sysinfo", 116)
SYS_syslog = Constant("SYS_syslog", 103)
SYS_tee = Constant("SYS_tee", 308)
SYS_tgkill = Constant("SYS_tgkill", 241)
SYS_time = Constant("SYS_time", 13)
SYS_timer_create = Constant("SYS_timer_create", 254)
SYS_timer_delete = Constant("SYS_timer_delete", (254 + 4))
SYS_timerfd = Constant("SYS_timerfd", 317)
SYS_timerfd_create = Constant("SYS_timerfd_create", 319)
SYS_timerfd_gettime = Constant("SYS_timerfd_gettime", 321)
SYS_timerfd_settime = Constant("SYS_timerfd_settime", 320)
SYS_timer_getoverrun = Constant("SYS_timer_getoverrun", (254 + 3))
SYS_timer_gettime = Constant("SYS_timer_gettime", (254 + 2))
SYS_timer_settime = Constant("SYS_timer_settime", (254 + 1))
SYS_times = Constant("SYS_times", 43)
SYS_tkill = Constant("SYS_tkill", 237)
SYS_truncate = Constant("SYS_truncate", 92)
SYS_truncate64 = Constant("SYS_truncate64", 193)
SYS_ugetrlimit = Constant("SYS_ugetrlimit", 191)
SYS_umask = Constant("SYS_umask", 60)
SYS_umount = Constant("SYS_umount", 22)
SYS_umount2 = Constant("SYS_umount2", 52)
SYS_uname = Constant("SYS_uname", 122)
SYS_unlink = Constant("SYS_unlink", 10)
SYS_unlinkat = Constant("SYS_unlinkat", 294)
SYS_unshare = Constant("SYS_unshare", 303)
SYS_uselib = Constant("SYS_uselib", 86)
SYS_ustat = Constant("SYS_ustat", 62)
SYS_utime = Constant("SYS_utime", 30)
SYS_utimensat = Constant("SYS_utimensat", 315)
SYS_utimes = Constant("SYS_utimes", 313)
SYS_vfork = Constant("SYS_vfork", 190)
SYS_vhangup = Constant("SYS_vhangup", 111)
SYS_vmsplice = Constant("SYS_vmsplice", 309)
SYS_wait4 = Constant("SYS_wait4", 114)
SYS_waitid = Constant("SYS_waitid", 281)
SYS_write = Constant("SYS_write", 4)
SYS_writev = Constant("SYS_writev", 146)
