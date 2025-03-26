/* Auto generated file. DO NOT EDIT */


#include <uk/print.h>
#include <uk/syscall.h>
#include "arch/regmap_linuxabi.h"

UK_SYSCALL_USC_PROLOGUE_DEFINE(uk_syscall6_r, uk_syscall6_r_u,
				14, long, nr, long, arg1, long, arg2, long, arg3, long, arg4, long, arg5, long, arg6)

long __used uk_syscall6_r_u(struct uk_syscall_ctx *usc)
{
	long ret;

	switch (usc->regs.rsyscall) {

#ifdef HAVE_uk_syscall_close
	case SYS_close:

#ifdef HAVE_uk_syscall_u_close
		ret = uk_syscall_r_u_close((long)usc);
#else /* !HAVE_uk_syscall_u_close */
		ret = uk_syscall_r_close(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_close */

		break;

#endif /* HAVE_uk_syscall_close */

#ifdef HAVE_uk_syscall_dup
	case SYS_dup:

#ifdef HAVE_uk_syscall_u_dup
		ret = uk_syscall_r_u_dup((long)usc);
#else /* !HAVE_uk_syscall_u_dup */
		ret = uk_syscall_r_dup(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_dup */

		break;

#endif /* HAVE_uk_syscall_dup */

#ifdef HAVE_uk_syscall_dup3
	case SYS_dup3:

#ifdef HAVE_uk_syscall_u_dup3
		ret = uk_syscall_r_u_dup3((long)usc);
#else /* !HAVE_uk_syscall_u_dup3 */
		ret = uk_syscall_r_dup3(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_dup3 */

		break;

#endif /* HAVE_uk_syscall_dup3 */

#ifdef HAVE_uk_syscall_dup2
	case SYS_dup2:

#ifdef HAVE_uk_syscall_u_dup2
		ret = uk_syscall_r_u_dup2((long)usc);
#else /* !HAVE_uk_syscall_u_dup2 */
		ret = uk_syscall_r_dup2(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_dup2 */

		break;

#endif /* HAVE_uk_syscall_dup2 */

#ifdef HAVE_uk_syscall_preadv2
	case SYS_preadv2:

#ifdef HAVE_uk_syscall_u_preadv2
		ret = uk_syscall_r_u_preadv2((long)usc);
#else /* !HAVE_uk_syscall_u_preadv2 */
		ret = uk_syscall_r_preadv2(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4);

#endif /* !HAVE_uk_syscall_u_preadv2 */

		break;

#endif /* HAVE_uk_syscall_preadv2 */

#ifdef HAVE_uk_syscall_preadv
	case SYS_preadv:

#ifdef HAVE_uk_syscall_u_preadv
		ret = uk_syscall_r_u_preadv((long)usc);
#else /* !HAVE_uk_syscall_u_preadv */
		ret = uk_syscall_r_preadv(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_preadv */

		break;

#endif /* HAVE_uk_syscall_preadv */

#ifdef HAVE_uk_syscall_pread64
	case SYS_pread64:

#ifdef HAVE_uk_syscall_u_pread64
		ret = uk_syscall_r_u_pread64((long)usc);
#else /* !HAVE_uk_syscall_u_pread64 */
		ret = uk_syscall_r_pread64(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_pread64 */

		break;

#endif /* HAVE_uk_syscall_pread64 */

#ifdef HAVE_uk_syscall_readv
	case SYS_readv:

#ifdef HAVE_uk_syscall_u_readv
		ret = uk_syscall_r_u_readv((long)usc);
#else /* !HAVE_uk_syscall_u_readv */
		ret = uk_syscall_r_readv(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_readv */

		break;

#endif /* HAVE_uk_syscall_readv */

#ifdef HAVE_uk_syscall_read
	case SYS_read:

#ifdef HAVE_uk_syscall_u_read
		ret = uk_syscall_r_u_read((long)usc);
#else /* !HAVE_uk_syscall_u_read */
		ret = uk_syscall_r_read(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_read */

		break;

#endif /* HAVE_uk_syscall_read */

#ifdef HAVE_uk_syscall_pwritev2
	case SYS_pwritev2:

#ifdef HAVE_uk_syscall_u_pwritev2
		ret = uk_syscall_r_u_pwritev2((long)usc);
#else /* !HAVE_uk_syscall_u_pwritev2 */
		ret = uk_syscall_r_pwritev2(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4);

#endif /* !HAVE_uk_syscall_u_pwritev2 */

		break;

#endif /* HAVE_uk_syscall_pwritev2 */

#ifdef HAVE_uk_syscall_pwritev
	case SYS_pwritev:

#ifdef HAVE_uk_syscall_u_pwritev
		ret = uk_syscall_r_u_pwritev((long)usc);
#else /* !HAVE_uk_syscall_u_pwritev */
		ret = uk_syscall_r_pwritev(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_pwritev */

		break;

#endif /* HAVE_uk_syscall_pwritev */

#ifdef HAVE_uk_syscall_pwrite64
	case SYS_pwrite64:

#ifdef HAVE_uk_syscall_u_pwrite64
		ret = uk_syscall_r_u_pwrite64((long)usc);
#else /* !HAVE_uk_syscall_u_pwrite64 */
		ret = uk_syscall_r_pwrite64(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_pwrite64 */

		break;

#endif /* HAVE_uk_syscall_pwrite64 */

#ifdef HAVE_uk_syscall_writev
	case SYS_writev:

#ifdef HAVE_uk_syscall_u_writev
		ret = uk_syscall_r_u_writev((long)usc);
#else /* !HAVE_uk_syscall_u_writev */
		ret = uk_syscall_r_writev(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_writev */

		break;

#endif /* HAVE_uk_syscall_writev */

#ifdef HAVE_uk_syscall_write
	case SYS_write:

#ifdef HAVE_uk_syscall_u_write
		ret = uk_syscall_r_u_write((long)usc);
#else /* !HAVE_uk_syscall_u_write */
		ret = uk_syscall_r_write(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_write */

		break;

#endif /* HAVE_uk_syscall_write */

#ifdef HAVE_uk_syscall_lseek
	case SYS_lseek:

#ifdef HAVE_uk_syscall_u_lseek
		ret = uk_syscall_r_u_lseek((long)usc);
#else /* !HAVE_uk_syscall_u_lseek */
		ret = uk_syscall_r_lseek(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_lseek */

		break;

#endif /* HAVE_uk_syscall_lseek */

#ifdef HAVE_uk_syscall_fstat
	case SYS_fstat:

#ifdef HAVE_uk_syscall_u_fstat
		ret = uk_syscall_r_u_fstat((long)usc);
#else /* !HAVE_uk_syscall_u_fstat */
		ret = uk_syscall_r_fstat(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_fstat */

		break;

#endif /* HAVE_uk_syscall_fstat */

#ifdef HAVE_uk_syscall_fcntl
	case SYS_fcntl:

#ifdef HAVE_uk_syscall_u_fcntl
		ret = uk_syscall_r_u_fcntl((long)usc);
#else /* !HAVE_uk_syscall_u_fcntl */
		ret = uk_syscall_r_fcntl(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_fcntl */

		break;

#endif /* HAVE_uk_syscall_fcntl */

#ifdef HAVE_uk_syscall_ioctl
	case SYS_ioctl:

#ifdef HAVE_uk_syscall_u_ioctl
		ret = uk_syscall_r_u_ioctl((long)usc);
#else /* !HAVE_uk_syscall_u_ioctl */
		ret = uk_syscall_r_ioctl(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_ioctl */

		break;

#endif /* HAVE_uk_syscall_ioctl */

#ifdef HAVE_uk_syscall_pipe
	case SYS_pipe:

#ifdef HAVE_uk_syscall_u_pipe
		ret = uk_syscall_r_u_pipe((long)usc);
#else /* !HAVE_uk_syscall_u_pipe */
		ret = uk_syscall_r_pipe(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_pipe */

		break;

#endif /* HAVE_uk_syscall_pipe */

#ifdef HAVE_uk_syscall_pipe2
	case SYS_pipe2:

#ifdef HAVE_uk_syscall_u_pipe2
		ret = uk_syscall_r_u_pipe2((long)usc);
#else /* !HAVE_uk_syscall_u_pipe2 */
		ret = uk_syscall_r_pipe2(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_pipe2 */

		break;

#endif /* HAVE_uk_syscall_pipe2 */

#ifdef HAVE_uk_syscall_poll
	case SYS_poll:

#ifdef HAVE_uk_syscall_u_poll
		ret = uk_syscall_r_u_poll((long)usc);
#else /* !HAVE_uk_syscall_u_poll */
		ret = uk_syscall_r_poll(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_poll */

		break;

#endif /* HAVE_uk_syscall_poll */

#ifdef HAVE_uk_syscall_ppoll
	case SYS_ppoll:

#ifdef HAVE_uk_syscall_u_ppoll
		ret = uk_syscall_r_u_ppoll((long)usc);
#else /* !HAVE_uk_syscall_u_ppoll */
		ret = uk_syscall_r_ppoll(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4);

#endif /* !HAVE_uk_syscall_u_ppoll */

		break;

#endif /* HAVE_uk_syscall_ppoll */

#ifdef HAVE_uk_syscall_select
	case SYS_select:

#ifdef HAVE_uk_syscall_u_select
		ret = uk_syscall_r_u_select((long)usc);
#else /* !HAVE_uk_syscall_u_select */
		ret = uk_syscall_r_select(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4);

#endif /* !HAVE_uk_syscall_u_select */

		break;

#endif /* HAVE_uk_syscall_select */

#ifdef HAVE_uk_syscall_pselect6
	case SYS_pselect6:

#ifdef HAVE_uk_syscall_u_pselect6
		ret = uk_syscall_r_u_pselect6((long)usc);
#else /* !HAVE_uk_syscall_u_pselect6 */
		ret = uk_syscall_r_pselect6(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4, usc->regs.rarg5);

#endif /* !HAVE_uk_syscall_u_pselect6 */

		break;

#endif /* HAVE_uk_syscall_pselect6 */

#ifdef HAVE_uk_syscall_epoll_create
	case SYS_epoll_create:

#ifdef HAVE_uk_syscall_u_epoll_create
		ret = uk_syscall_r_u_epoll_create((long)usc);
#else /* !HAVE_uk_syscall_u_epoll_create */
		ret = uk_syscall_r_epoll_create(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_epoll_create */

		break;

#endif /* HAVE_uk_syscall_epoll_create */

#ifdef HAVE_uk_syscall_epoll_create1
	case SYS_epoll_create1:

#ifdef HAVE_uk_syscall_u_epoll_create1
		ret = uk_syscall_r_u_epoll_create1((long)usc);
#else /* !HAVE_uk_syscall_u_epoll_create1 */
		ret = uk_syscall_r_epoll_create1(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_epoll_create1 */

		break;

#endif /* HAVE_uk_syscall_epoll_create1 */

#ifdef HAVE_uk_syscall_epoll_ctl
	case SYS_epoll_ctl:

#ifdef HAVE_uk_syscall_u_epoll_ctl
		ret = uk_syscall_r_u_epoll_ctl((long)usc);
#else /* !HAVE_uk_syscall_u_epoll_ctl */
		ret = uk_syscall_r_epoll_ctl(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_epoll_ctl */

		break;

#endif /* HAVE_uk_syscall_epoll_ctl */

#ifdef HAVE_uk_syscall_epoll_wait
	case SYS_epoll_wait:

#ifdef HAVE_uk_syscall_u_epoll_wait
		ret = uk_syscall_r_u_epoll_wait((long)usc);
#else /* !HAVE_uk_syscall_u_epoll_wait */
		ret = uk_syscall_r_epoll_wait(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_epoll_wait */

		break;

#endif /* HAVE_uk_syscall_epoll_wait */

#ifdef HAVE_uk_syscall_epoll_pwait
	case SYS_epoll_pwait:

#ifdef HAVE_uk_syscall_u_epoll_pwait
		ret = uk_syscall_r_u_epoll_pwait((long)usc);
#else /* !HAVE_uk_syscall_u_epoll_pwait */
		ret = uk_syscall_r_epoll_pwait(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4, usc->regs.rarg5);

#endif /* !HAVE_uk_syscall_u_epoll_pwait */

		break;

#endif /* HAVE_uk_syscall_epoll_pwait */

#ifdef HAVE_uk_syscall_epoll_pwait2
	case SYS_epoll_pwait2:

#ifdef HAVE_uk_syscall_u_epoll_pwait2
		ret = uk_syscall_r_u_epoll_pwait2((long)usc);
#else /* !HAVE_uk_syscall_u_epoll_pwait2 */
		ret = uk_syscall_r_epoll_pwait2(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4, usc->regs.rarg5);

#endif /* !HAVE_uk_syscall_u_epoll_pwait2 */

		break;

#endif /* HAVE_uk_syscall_epoll_pwait2 */

#ifdef HAVE_uk_syscall_clone
	case SYS_clone:

#ifdef HAVE_uk_syscall_u_clone
		ret = uk_syscall_r_u_clone((long)usc);
#else /* !HAVE_uk_syscall_u_clone */
		ret = uk_syscall_r_clone(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4);

#endif /* !HAVE_uk_syscall_u_clone */

		break;

#endif /* HAVE_uk_syscall_clone */

#ifdef HAVE_uk_syscall_execve
	case SYS_execve:

#ifdef HAVE_uk_syscall_u_execve
		ret = uk_syscall_r_u_execve((long)usc);
#else /* !HAVE_uk_syscall_u_execve */
		ret = uk_syscall_r_execve(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_execve */

		break;

#endif /* HAVE_uk_syscall_execve */

#ifdef HAVE_uk_syscall_wait4
	case SYS_wait4:

#ifdef HAVE_uk_syscall_u_wait4
		ret = uk_syscall_r_u_wait4((long)usc);
#else /* !HAVE_uk_syscall_u_wait4 */
		ret = uk_syscall_r_wait4(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_wait4 */

		break;

#endif /* HAVE_uk_syscall_wait4 */

#ifdef HAVE_uk_syscall_waitid
	case SYS_waitid:

#ifdef HAVE_uk_syscall_u_waitid
		ret = uk_syscall_r_u_waitid((long)usc);
#else /* !HAVE_uk_syscall_u_waitid */
		ret = uk_syscall_r_waitid(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_waitid */

		break;

#endif /* HAVE_uk_syscall_waitid */

#ifdef HAVE_uk_syscall_getpgid
	case SYS_getpgid:

#ifdef HAVE_uk_syscall_u_getpgid
		ret = uk_syscall_r_u_getpgid((long)usc);
#else /* !HAVE_uk_syscall_u_getpgid */
		ret = uk_syscall_r_getpgid(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_getpgid */

		break;

#endif /* HAVE_uk_syscall_getpgid */

#ifdef HAVE_uk_syscall_setpgid
	case SYS_setpgid:

#ifdef HAVE_uk_syscall_u_setpgid
		ret = uk_syscall_r_u_setpgid((long)usc);
#else /* !HAVE_uk_syscall_u_setpgid */
		ret = uk_syscall_r_setpgid(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_setpgid */

		break;

#endif /* HAVE_uk_syscall_setpgid */

#ifdef HAVE_uk_syscall_setsid
	case SYS_setsid:

#ifdef HAVE_uk_syscall_u_setsid
		ret = uk_syscall_r_u_setsid((long)usc);
#else /* !HAVE_uk_syscall_u_setsid */
		ret = uk_syscall_r_setsid(
					);

#endif /* !HAVE_uk_syscall_u_setsid */

		break;

#endif /* HAVE_uk_syscall_setsid */

#ifdef HAVE_uk_syscall_getsid
	case SYS_getsid:

#ifdef HAVE_uk_syscall_u_getsid
		ret = uk_syscall_r_u_getsid((long)usc);
#else /* !HAVE_uk_syscall_u_getsid */
		ret = uk_syscall_r_getsid(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_getsid */

		break;

#endif /* HAVE_uk_syscall_getsid */

#ifdef HAVE_uk_syscall_setpriority
	case SYS_setpriority:

#ifdef HAVE_uk_syscall_u_setpriority
		ret = uk_syscall_r_u_setpriority((long)usc);
#else /* !HAVE_uk_syscall_u_setpriority */
		ret = uk_syscall_r_setpriority(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_setpriority */

		break;

#endif /* HAVE_uk_syscall_setpriority */

#ifdef HAVE_uk_syscall_getpriority
	case SYS_getpriority:

#ifdef HAVE_uk_syscall_u_getpriority
		ret = uk_syscall_r_u_getpriority((long)usc);
#else /* !HAVE_uk_syscall_u_getpriority */
		ret = uk_syscall_r_getpriority(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_getpriority */

		break;

#endif /* HAVE_uk_syscall_getpriority */

#ifdef HAVE_uk_syscall_getpgrp
	case SYS_getpgrp:

#ifdef HAVE_uk_syscall_u_getpgrp
		ret = uk_syscall_r_u_getpgrp((long)usc);
#else /* !HAVE_uk_syscall_u_getpgrp */
		ret = uk_syscall_r_getpgrp(
					);

#endif /* !HAVE_uk_syscall_u_getpgrp */

		break;

#endif /* HAVE_uk_syscall_getpgrp */

#ifdef HAVE_uk_syscall_getpid
	case SYS_getpid:

#ifdef HAVE_uk_syscall_u_getpid
		ret = uk_syscall_r_u_getpid((long)usc);
#else /* !HAVE_uk_syscall_u_getpid */
		ret = uk_syscall_r_getpid(
					);

#endif /* !HAVE_uk_syscall_u_getpid */

		break;

#endif /* HAVE_uk_syscall_getpid */

#ifdef HAVE_uk_syscall_gettid
	case SYS_gettid:

#ifdef HAVE_uk_syscall_u_gettid
		ret = uk_syscall_r_u_gettid((long)usc);
#else /* !HAVE_uk_syscall_u_gettid */
		ret = uk_syscall_r_gettid(
					);

#endif /* !HAVE_uk_syscall_u_gettid */

		break;

#endif /* HAVE_uk_syscall_gettid */

#ifdef HAVE_uk_syscall_getppid
	case SYS_getppid:

#ifdef HAVE_uk_syscall_u_getppid
		ret = uk_syscall_r_u_getppid((long)usc);
#else /* !HAVE_uk_syscall_u_getppid */
		ret = uk_syscall_r_getppid(
					);

#endif /* !HAVE_uk_syscall_u_getppid */

		break;

#endif /* HAVE_uk_syscall_getppid */

#ifdef HAVE_uk_syscall_prlimit64
	case SYS_prlimit64:

#ifdef HAVE_uk_syscall_u_prlimit64
		ret = uk_syscall_r_u_prlimit64((long)usc);
#else /* !HAVE_uk_syscall_u_prlimit64 */
		ret = uk_syscall_r_prlimit64(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_prlimit64 */

		break;

#endif /* HAVE_uk_syscall_prlimit64 */

#ifdef HAVE_uk_syscall_getrlimit
	case SYS_getrlimit:

#ifdef HAVE_uk_syscall_u_getrlimit
		ret = uk_syscall_r_u_getrlimit((long)usc);
#else /* !HAVE_uk_syscall_u_getrlimit */
		ret = uk_syscall_r_getrlimit(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_getrlimit */

		break;

#endif /* HAVE_uk_syscall_getrlimit */

#ifdef HAVE_uk_syscall_setrlimit
	case SYS_setrlimit:

#ifdef HAVE_uk_syscall_u_setrlimit
		ret = uk_syscall_r_u_setrlimit((long)usc);
#else /* !HAVE_uk_syscall_u_setrlimit */
		ret = uk_syscall_r_setrlimit(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_setrlimit */

		break;

#endif /* HAVE_uk_syscall_setrlimit */

#ifdef HAVE_uk_syscall_getrusage
	case SYS_getrusage:

#ifdef HAVE_uk_syscall_u_getrusage
		ret = uk_syscall_r_u_getrusage((long)usc);
#else /* !HAVE_uk_syscall_u_getrusage */
		ret = uk_syscall_r_getrusage(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_getrusage */

		break;

#endif /* HAVE_uk_syscall_getrusage */

#ifdef HAVE_uk_syscall_prctl
	case SYS_prctl:

#ifdef HAVE_uk_syscall_u_prctl
		ret = uk_syscall_r_u_prctl((long)usc);
#else /* !HAVE_uk_syscall_u_prctl */
		ret = uk_syscall_r_prctl(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4);

#endif /* !HAVE_uk_syscall_u_prctl */

		break;

#endif /* HAVE_uk_syscall_prctl */

#ifdef HAVE_uk_syscall_exit
	case SYS_exit:

#ifdef HAVE_uk_syscall_u_exit
		ret = uk_syscall_r_u_exit((long)usc);
#else /* !HAVE_uk_syscall_u_exit */
		ret = uk_syscall_r_exit(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_exit */

		break;

#endif /* HAVE_uk_syscall_exit */

#ifdef HAVE_uk_syscall_exit_group
	case SYS_exit_group:

#ifdef HAVE_uk_syscall_u_exit_group
		ret = uk_syscall_r_u_exit_group((long)usc);
#else /* !HAVE_uk_syscall_u_exit_group */
		ret = uk_syscall_r_exit_group(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_exit_group */

		break;

#endif /* HAVE_uk_syscall_exit_group */

#ifdef HAVE_uk_syscall_socket
	case SYS_socket:

#ifdef HAVE_uk_syscall_u_socket
		ret = uk_syscall_r_u_socket((long)usc);
#else /* !HAVE_uk_syscall_u_socket */
		ret = uk_syscall_r_socket(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_socket */

		break;

#endif /* HAVE_uk_syscall_socket */

#ifdef HAVE_uk_syscall_accept
	case SYS_accept:

#ifdef HAVE_uk_syscall_u_accept
		ret = uk_syscall_r_u_accept((long)usc);
#else /* !HAVE_uk_syscall_u_accept */
		ret = uk_syscall_r_accept(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_accept */

		break;

#endif /* HAVE_uk_syscall_accept */

#ifdef HAVE_uk_syscall_accept4
	case SYS_accept4:

#ifdef HAVE_uk_syscall_u_accept4
		ret = uk_syscall_r_u_accept4((long)usc);
#else /* !HAVE_uk_syscall_u_accept4 */
		ret = uk_syscall_r_accept4(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_accept4 */

		break;

#endif /* HAVE_uk_syscall_accept4 */

#ifdef HAVE_uk_syscall_getsockopt
	case SYS_getsockopt:

#ifdef HAVE_uk_syscall_u_getsockopt
		ret = uk_syscall_r_u_getsockopt((long)usc);
#else /* !HAVE_uk_syscall_u_getsockopt */
		ret = uk_syscall_r_getsockopt(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4);

#endif /* !HAVE_uk_syscall_u_getsockopt */

		break;

#endif /* HAVE_uk_syscall_getsockopt */

#ifdef HAVE_uk_syscall_setsockopt
	case SYS_setsockopt:

#ifdef HAVE_uk_syscall_u_setsockopt
		ret = uk_syscall_r_u_setsockopt((long)usc);
#else /* !HAVE_uk_syscall_u_setsockopt */
		ret = uk_syscall_r_setsockopt(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4);

#endif /* !HAVE_uk_syscall_u_setsockopt */

		break;

#endif /* HAVE_uk_syscall_setsockopt */

#ifdef HAVE_uk_syscall_bind
	case SYS_bind:

#ifdef HAVE_uk_syscall_u_bind
		ret = uk_syscall_r_u_bind((long)usc);
#else /* !HAVE_uk_syscall_u_bind */
		ret = uk_syscall_r_bind(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_bind */

		break;

#endif /* HAVE_uk_syscall_bind */

#ifdef HAVE_uk_syscall_listen
	case SYS_listen:

#ifdef HAVE_uk_syscall_u_listen
		ret = uk_syscall_r_u_listen((long)usc);
#else /* !HAVE_uk_syscall_u_listen */
		ret = uk_syscall_r_listen(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_listen */

		break;

#endif /* HAVE_uk_syscall_listen */

#ifdef HAVE_uk_syscall_connect
	case SYS_connect:

#ifdef HAVE_uk_syscall_u_connect
		ret = uk_syscall_r_u_connect((long)usc);
#else /* !HAVE_uk_syscall_u_connect */
		ret = uk_syscall_r_connect(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_connect */

		break;

#endif /* HAVE_uk_syscall_connect */

#ifdef HAVE_uk_syscall_getpeername
	case SYS_getpeername:

#ifdef HAVE_uk_syscall_u_getpeername
		ret = uk_syscall_r_u_getpeername((long)usc);
#else /* !HAVE_uk_syscall_u_getpeername */
		ret = uk_syscall_r_getpeername(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_getpeername */

		break;

#endif /* HAVE_uk_syscall_getpeername */

#ifdef HAVE_uk_syscall_getsockname
	case SYS_getsockname:

#ifdef HAVE_uk_syscall_u_getsockname
		ret = uk_syscall_r_u_getsockname((long)usc);
#else /* !HAVE_uk_syscall_u_getsockname */
		ret = uk_syscall_r_getsockname(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_getsockname */

		break;

#endif /* HAVE_uk_syscall_getsockname */

#ifdef HAVE_uk_syscall_recvfrom
	case SYS_recvfrom:

#ifdef HAVE_uk_syscall_u_recvfrom
		ret = uk_syscall_r_u_recvfrom((long)usc);
#else /* !HAVE_uk_syscall_u_recvfrom */
		ret = uk_syscall_r_recvfrom(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4, usc->regs.rarg5);

#endif /* !HAVE_uk_syscall_u_recvfrom */

		break;

#endif /* HAVE_uk_syscall_recvfrom */

#ifdef HAVE_uk_syscall_recvmsg
	case SYS_recvmsg:

#ifdef HAVE_uk_syscall_u_recvmsg
		ret = uk_syscall_r_u_recvmsg((long)usc);
#else /* !HAVE_uk_syscall_u_recvmsg */
		ret = uk_syscall_r_recvmsg(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_recvmsg */

		break;

#endif /* HAVE_uk_syscall_recvmsg */

#ifdef HAVE_uk_syscall_sendto
	case SYS_sendto:

#ifdef HAVE_uk_syscall_u_sendto
		ret = uk_syscall_r_u_sendto((long)usc);
#else /* !HAVE_uk_syscall_u_sendto */
		ret = uk_syscall_r_sendto(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4, usc->regs.rarg5);

#endif /* !HAVE_uk_syscall_u_sendto */

		break;

#endif /* HAVE_uk_syscall_sendto */

#ifdef HAVE_uk_syscall_sendmsg
	case SYS_sendmsg:

#ifdef HAVE_uk_syscall_u_sendmsg
		ret = uk_syscall_r_u_sendmsg((long)usc);
#else /* !HAVE_uk_syscall_u_sendmsg */
		ret = uk_syscall_r_sendmsg(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_sendmsg */

		break;

#endif /* HAVE_uk_syscall_sendmsg */

#ifdef HAVE_uk_syscall_socketpair
	case SYS_socketpair:

#ifdef HAVE_uk_syscall_u_socketpair
		ret = uk_syscall_r_u_socketpair((long)usc);
#else /* !HAVE_uk_syscall_u_socketpair */
		ret = uk_syscall_r_socketpair(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_socketpair */

		break;

#endif /* HAVE_uk_syscall_socketpair */

#ifdef HAVE_uk_syscall_shutdown
	case SYS_shutdown:

#ifdef HAVE_uk_syscall_u_shutdown
		ret = uk_syscall_r_u_shutdown((long)usc);
#else /* !HAVE_uk_syscall_u_shutdown */
		ret = uk_syscall_r_shutdown(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_shutdown */

		break;

#endif /* HAVE_uk_syscall_shutdown */

#ifdef HAVE_uk_syscall_futex
	case SYS_futex:

#ifdef HAVE_uk_syscall_u_futex
		ret = uk_syscall_r_u_futex((long)usc);
#else /* !HAVE_uk_syscall_u_futex */
		ret = uk_syscall_r_futex(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4, usc->regs.rarg5);

#endif /* !HAVE_uk_syscall_u_futex */

		break;

#endif /* HAVE_uk_syscall_futex */

#ifdef HAVE_uk_syscall_set_tid_address
	case SYS_set_tid_address:

#ifdef HAVE_uk_syscall_u_set_tid_address
		ret = uk_syscall_r_u_set_tid_address((long)usc);
#else /* !HAVE_uk_syscall_u_set_tid_address */
		ret = uk_syscall_r_set_tid_address(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_set_tid_address */

		break;

#endif /* HAVE_uk_syscall_set_tid_address */

#ifdef HAVE_uk_syscall_getuid
	case SYS_getuid:

#ifdef HAVE_uk_syscall_u_getuid
		ret = uk_syscall_r_u_getuid((long)usc);
#else /* !HAVE_uk_syscall_u_getuid */
		ret = uk_syscall_r_getuid(
					);

#endif /* !HAVE_uk_syscall_u_getuid */

		break;

#endif /* HAVE_uk_syscall_getuid */

#ifdef HAVE_uk_syscall_setuid
	case SYS_setuid:

#ifdef HAVE_uk_syscall_u_setuid
		ret = uk_syscall_r_u_setuid((long)usc);
#else /* !HAVE_uk_syscall_u_setuid */
		ret = uk_syscall_r_setuid(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_setuid */

		break;

#endif /* HAVE_uk_syscall_setuid */

#ifdef HAVE_uk_syscall_geteuid
	case SYS_geteuid:

#ifdef HAVE_uk_syscall_u_geteuid
		ret = uk_syscall_r_u_geteuid((long)usc);
#else /* !HAVE_uk_syscall_u_geteuid */
		ret = uk_syscall_r_geteuid(
					);

#endif /* !HAVE_uk_syscall_u_geteuid */

		break;

#endif /* HAVE_uk_syscall_geteuid */

#ifdef HAVE_uk_syscall_setreuid
	case SYS_setreuid:

#ifdef HAVE_uk_syscall_u_setreuid
		ret = uk_syscall_r_u_setreuid((long)usc);
#else /* !HAVE_uk_syscall_u_setreuid */
		ret = uk_syscall_r_setreuid(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_setreuid */

		break;

#endif /* HAVE_uk_syscall_setreuid */

#ifdef HAVE_uk_syscall_getresuid
	case SYS_getresuid:

#ifdef HAVE_uk_syscall_u_getresuid
		ret = uk_syscall_r_u_getresuid((long)usc);
#else /* !HAVE_uk_syscall_u_getresuid */
		ret = uk_syscall_r_getresuid(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_getresuid */

		break;

#endif /* HAVE_uk_syscall_getresuid */

#ifdef HAVE_uk_syscall_setresuid
	case SYS_setresuid:

#ifdef HAVE_uk_syscall_u_setresuid
		ret = uk_syscall_r_u_setresuid((long)usc);
#else /* !HAVE_uk_syscall_u_setresuid */
		ret = uk_syscall_r_setresuid(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_setresuid */

		break;

#endif /* HAVE_uk_syscall_setresuid */

#ifdef HAVE_uk_syscall_setfsuid
	case SYS_setfsuid:

#ifdef HAVE_uk_syscall_u_setfsuid
		ret = uk_syscall_r_u_setfsuid((long)usc);
#else /* !HAVE_uk_syscall_u_setfsuid */
		ret = uk_syscall_r_setfsuid(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_setfsuid */

		break;

#endif /* HAVE_uk_syscall_setfsuid */

#ifdef HAVE_uk_syscall_getgid
	case SYS_getgid:

#ifdef HAVE_uk_syscall_u_getgid
		ret = uk_syscall_r_u_getgid((long)usc);
#else /* !HAVE_uk_syscall_u_getgid */
		ret = uk_syscall_r_getgid(
					);

#endif /* !HAVE_uk_syscall_u_getgid */

		break;

#endif /* HAVE_uk_syscall_getgid */

#ifdef HAVE_uk_syscall_setgid
	case SYS_setgid:

#ifdef HAVE_uk_syscall_u_setgid
		ret = uk_syscall_r_u_setgid((long)usc);
#else /* !HAVE_uk_syscall_u_setgid */
		ret = uk_syscall_r_setgid(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_setgid */

		break;

#endif /* HAVE_uk_syscall_setgid */

#ifdef HAVE_uk_syscall_getegid
	case SYS_getegid:

#ifdef HAVE_uk_syscall_u_getegid
		ret = uk_syscall_r_u_getegid((long)usc);
#else /* !HAVE_uk_syscall_u_getegid */
		ret = uk_syscall_r_getegid(
					);

#endif /* !HAVE_uk_syscall_u_getegid */

		break;

#endif /* HAVE_uk_syscall_getegid */

#ifdef HAVE_uk_syscall_setregid
	case SYS_setregid:

#ifdef HAVE_uk_syscall_u_setregid
		ret = uk_syscall_r_u_setregid((long)usc);
#else /* !HAVE_uk_syscall_u_setregid */
		ret = uk_syscall_r_setregid(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_setregid */

		break;

#endif /* HAVE_uk_syscall_setregid */

#ifdef HAVE_uk_syscall_getresgid
	case SYS_getresgid:

#ifdef HAVE_uk_syscall_u_getresgid
		ret = uk_syscall_r_u_getresgid((long)usc);
#else /* !HAVE_uk_syscall_u_getresgid */
		ret = uk_syscall_r_getresgid(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_getresgid */

		break;

#endif /* HAVE_uk_syscall_getresgid */

#ifdef HAVE_uk_syscall_setresgid
	case SYS_setresgid:

#ifdef HAVE_uk_syscall_u_setresgid
		ret = uk_syscall_r_u_setresgid((long)usc);
#else /* !HAVE_uk_syscall_u_setresgid */
		ret = uk_syscall_r_setresgid(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_setresgid */

		break;

#endif /* HAVE_uk_syscall_setresgid */

#ifdef HAVE_uk_syscall_setfsgid
	case SYS_setfsgid:

#ifdef HAVE_uk_syscall_u_setfsgid
		ret = uk_syscall_r_u_setfsgid((long)usc);
#else /* !HAVE_uk_syscall_u_setfsgid */
		ret = uk_syscall_r_setfsgid(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_setfsgid */

		break;

#endif /* HAVE_uk_syscall_setfsgid */

#ifdef HAVE_uk_syscall_getgroups
	case SYS_getgroups:

#ifdef HAVE_uk_syscall_u_getgroups
		ret = uk_syscall_r_u_getgroups((long)usc);
#else /* !HAVE_uk_syscall_u_getgroups */
		ret = uk_syscall_r_getgroups(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_getgroups */

		break;

#endif /* HAVE_uk_syscall_getgroups */

#ifdef HAVE_uk_syscall_setgroups
	case SYS_setgroups:

#ifdef HAVE_uk_syscall_u_setgroups
		ret = uk_syscall_r_u_setgroups((long)usc);
#else /* !HAVE_uk_syscall_u_setgroups */
		ret = uk_syscall_r_setgroups(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_setgroups */

		break;

#endif /* HAVE_uk_syscall_setgroups */

#ifdef HAVE_uk_syscall_capget
	case SYS_capget:

#ifdef HAVE_uk_syscall_u_capget
		ret = uk_syscall_r_u_capget((long)usc);
#else /* !HAVE_uk_syscall_u_capget */
		ret = uk_syscall_r_capget(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_capget */

		break;

#endif /* HAVE_uk_syscall_capget */

#ifdef HAVE_uk_syscall_capset
	case SYS_capset:

#ifdef HAVE_uk_syscall_u_capset
		ret = uk_syscall_r_u_capset((long)usc);
#else /* !HAVE_uk_syscall_u_capset */
		ret = uk_syscall_r_capset(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_capset */

		break;

#endif /* HAVE_uk_syscall_capset */

#ifdef HAVE_uk_syscall_mmap
	case SYS_mmap:

#ifdef HAVE_uk_syscall_u_mmap
		ret = uk_syscall_r_u_mmap((long)usc);
#else /* !HAVE_uk_syscall_u_mmap */
		ret = uk_syscall_r_mmap(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4, usc->regs.rarg5);

#endif /* !HAVE_uk_syscall_u_mmap */

		break;

#endif /* HAVE_uk_syscall_mmap */

#ifdef HAVE_uk_syscall_munmap
	case SYS_munmap:

#ifdef HAVE_uk_syscall_u_munmap
		ret = uk_syscall_r_u_munmap((long)usc);
#else /* !HAVE_uk_syscall_u_munmap */
		ret = uk_syscall_r_munmap(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_munmap */

		break;

#endif /* HAVE_uk_syscall_munmap */

#ifdef HAVE_uk_syscall_madvise
	case SYS_madvise:

#ifdef HAVE_uk_syscall_u_madvise
		ret = uk_syscall_r_u_madvise((long)usc);
#else /* !HAVE_uk_syscall_u_madvise */
		ret = uk_syscall_r_madvise(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_madvise */

		break;

#endif /* HAVE_uk_syscall_madvise */

#ifdef HAVE_uk_syscall_mremap
	case SYS_mremap:

#ifdef HAVE_uk_syscall_u_mremap
		ret = uk_syscall_r_u_mremap((long)usc);
#else /* !HAVE_uk_syscall_u_mremap */
		ret = uk_syscall_r_mremap(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4);

#endif /* !HAVE_uk_syscall_u_mremap */

		break;

#endif /* HAVE_uk_syscall_mremap */

#ifdef HAVE_uk_syscall_mprotect
	case SYS_mprotect:

#ifdef HAVE_uk_syscall_u_mprotect
		ret = uk_syscall_r_u_mprotect((long)usc);
#else /* !HAVE_uk_syscall_u_mprotect */
		ret = uk_syscall_r_mprotect(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_mprotect */

		break;

#endif /* HAVE_uk_syscall_mprotect */

#ifdef HAVE_uk_syscall_sched_yield
	case SYS_sched_yield:

#ifdef HAVE_uk_syscall_u_sched_yield
		ret = uk_syscall_r_u_sched_yield((long)usc);
#else /* !HAVE_uk_syscall_u_sched_yield */
		ret = uk_syscall_r_sched_yield(
					);

#endif /* !HAVE_uk_syscall_u_sched_yield */

		break;

#endif /* HAVE_uk_syscall_sched_yield */

#ifdef HAVE_uk_syscall_sched_getaffinity
	case SYS_sched_getaffinity:

#ifdef HAVE_uk_syscall_u_sched_getaffinity
		ret = uk_syscall_r_u_sched_getaffinity((long)usc);
#else /* !HAVE_uk_syscall_u_sched_getaffinity */
		ret = uk_syscall_r_sched_getaffinity(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_sched_getaffinity */

		break;

#endif /* HAVE_uk_syscall_sched_getaffinity */

#ifdef HAVE_uk_syscall_sched_setaffinity
	case SYS_sched_setaffinity:

#ifdef HAVE_uk_syscall_u_sched_setaffinity
		ret = uk_syscall_r_u_sched_setaffinity((long)usc);
#else /* !HAVE_uk_syscall_u_sched_setaffinity */
		ret = uk_syscall_r_sched_setaffinity(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_sched_setaffinity */

		break;

#endif /* HAVE_uk_syscall_sched_setaffinity */

#ifdef HAVE_uk_syscall_membarrier
	case SYS_membarrier:

#ifdef HAVE_uk_syscall_u_membarrier
		ret = uk_syscall_r_u_membarrier((long)usc);
#else /* !HAVE_uk_syscall_u_membarrier */
		ret = uk_syscall_r_membarrier(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_membarrier */

		break;

#endif /* HAVE_uk_syscall_membarrier */

#ifdef HAVE_uk_syscall_sigaltstack
	case SYS_sigaltstack:

#ifdef HAVE_uk_syscall_u_sigaltstack
		ret = uk_syscall_r_u_sigaltstack((long)usc);
#else /* !HAVE_uk_syscall_u_sigaltstack */
		ret = uk_syscall_r_sigaltstack(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_sigaltstack */

		break;

#endif /* HAVE_uk_syscall_sigaltstack */

#ifdef HAVE_uk_syscall_rt_sigaction
	case SYS_rt_sigaction:

#ifdef HAVE_uk_syscall_u_rt_sigaction
		ret = uk_syscall_r_u_rt_sigaction((long)usc);
#else /* !HAVE_uk_syscall_u_rt_sigaction */
		ret = uk_syscall_r_rt_sigaction(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_rt_sigaction */

		break;

#endif /* HAVE_uk_syscall_rt_sigaction */

#ifdef HAVE_uk_syscall_rt_sigprocmask
	case SYS_rt_sigprocmask:

#ifdef HAVE_uk_syscall_u_rt_sigprocmask
		ret = uk_syscall_r_u_rt_sigprocmask((long)usc);
#else /* !HAVE_uk_syscall_u_rt_sigprocmask */
		ret = uk_syscall_r_rt_sigprocmask(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_rt_sigprocmask */

		break;

#endif /* HAVE_uk_syscall_rt_sigprocmask */

#ifdef HAVE_uk_syscall_rt_sigpending
	case SYS_rt_sigpending:

#ifdef HAVE_uk_syscall_u_rt_sigpending
		ret = uk_syscall_r_u_rt_sigpending((long)usc);
#else /* !HAVE_uk_syscall_u_rt_sigpending */
		ret = uk_syscall_r_rt_sigpending(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_rt_sigpending */

		break;

#endif /* HAVE_uk_syscall_rt_sigpending */

#ifdef HAVE_uk_syscall_rt_sigsuspend
	case SYS_rt_sigsuspend:

#ifdef HAVE_uk_syscall_u_rt_sigsuspend
		ret = uk_syscall_r_u_rt_sigsuspend((long)usc);
#else /* !HAVE_uk_syscall_u_rt_sigsuspend */
		ret = uk_syscall_r_rt_sigsuspend(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_rt_sigsuspend */

		break;

#endif /* HAVE_uk_syscall_rt_sigsuspend */

#ifdef HAVE_uk_syscall_rt_sigtimedwait
	case SYS_rt_sigtimedwait:

#ifdef HAVE_uk_syscall_u_rt_sigtimedwait
		ret = uk_syscall_r_u_rt_sigtimedwait((long)usc);
#else /* !HAVE_uk_syscall_u_rt_sigtimedwait */
		ret = uk_syscall_r_rt_sigtimedwait(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_rt_sigtimedwait */

		break;

#endif /* HAVE_uk_syscall_rt_sigtimedwait */

#ifdef HAVE_uk_syscall_kill
	case SYS_kill:

#ifdef HAVE_uk_syscall_u_kill
		ret = uk_syscall_r_u_kill((long)usc);
#else /* !HAVE_uk_syscall_u_kill */
		ret = uk_syscall_r_kill(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_kill */

		break;

#endif /* HAVE_uk_syscall_kill */

#ifdef HAVE_uk_syscall_tkill
	case SYS_tkill:

#ifdef HAVE_uk_syscall_u_tkill
		ret = uk_syscall_r_u_tkill((long)usc);
#else /* !HAVE_uk_syscall_u_tkill */
		ret = uk_syscall_r_tkill(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_tkill */

		break;

#endif /* HAVE_uk_syscall_tkill */

#ifdef HAVE_uk_syscall_alarm
	case SYS_alarm:

#ifdef HAVE_uk_syscall_u_alarm
		ret = uk_syscall_r_u_alarm((long)usc);
#else /* !HAVE_uk_syscall_u_alarm */
		ret = uk_syscall_r_alarm(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_alarm */

		break;

#endif /* HAVE_uk_syscall_alarm */

#ifdef HAVE_uk_syscall_pause
	case SYS_pause:

#ifdef HAVE_uk_syscall_u_pause
		ret = uk_syscall_r_u_pause((long)usc);
#else /* !HAVE_uk_syscall_u_pause */
		ret = uk_syscall_r_pause(
					);

#endif /* !HAVE_uk_syscall_u_pause */

		break;

#endif /* HAVE_uk_syscall_pause */

#ifdef HAVE_uk_syscall_nanosleep
	case SYS_nanosleep:

#ifdef HAVE_uk_syscall_u_nanosleep
		ret = uk_syscall_r_u_nanosleep((long)usc);
#else /* !HAVE_uk_syscall_u_nanosleep */
		ret = uk_syscall_r_nanosleep(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_nanosleep */

		break;

#endif /* HAVE_uk_syscall_nanosleep */

#ifdef HAVE_uk_syscall_clock_getres
	case SYS_clock_getres:

#ifdef HAVE_uk_syscall_u_clock_getres
		ret = uk_syscall_r_u_clock_getres((long)usc);
#else /* !HAVE_uk_syscall_u_clock_getres */
		ret = uk_syscall_r_clock_getres(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_clock_getres */

		break;

#endif /* HAVE_uk_syscall_clock_getres */

#ifdef HAVE_uk_syscall_clock_gettime
	case SYS_clock_gettime:

#ifdef HAVE_uk_syscall_u_clock_gettime
		ret = uk_syscall_r_u_clock_gettime((long)usc);
#else /* !HAVE_uk_syscall_u_clock_gettime */
		ret = uk_syscall_r_clock_gettime(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_clock_gettime */

		break;

#endif /* HAVE_uk_syscall_clock_gettime */

#ifdef HAVE_uk_syscall_clock_settime
	case SYS_clock_settime:

#ifdef HAVE_uk_syscall_u_clock_settime
		ret = uk_syscall_r_u_clock_settime((long)usc);
#else /* !HAVE_uk_syscall_u_clock_settime */
		ret = uk_syscall_r_clock_settime(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_clock_settime */

		break;

#endif /* HAVE_uk_syscall_clock_settime */

#ifdef HAVE_uk_syscall_clock_nanosleep
	case SYS_clock_nanosleep:

#ifdef HAVE_uk_syscall_u_clock_nanosleep
		ret = uk_syscall_r_u_clock_nanosleep((long)usc);
#else /* !HAVE_uk_syscall_u_clock_nanosleep */
		ret = uk_syscall_r_clock_nanosleep(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_clock_nanosleep */

		break;

#endif /* HAVE_uk_syscall_clock_nanosleep */

#ifdef HAVE_uk_syscall_gettimeofday
	case SYS_gettimeofday:

#ifdef HAVE_uk_syscall_u_gettimeofday
		ret = uk_syscall_r_u_gettimeofday((long)usc);
#else /* !HAVE_uk_syscall_u_gettimeofday */
		ret = uk_syscall_r_gettimeofday(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_gettimeofday */

		break;

#endif /* HAVE_uk_syscall_gettimeofday */

#ifdef HAVE_uk_syscall_times
	case SYS_times:

#ifdef HAVE_uk_syscall_u_times
		ret = uk_syscall_r_u_times((long)usc);
#else /* !HAVE_uk_syscall_u_times */
		ret = uk_syscall_r_times(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_times */

		break;

#endif /* HAVE_uk_syscall_times */

#ifdef HAVE_uk_syscall_time
	case SYS_time:

#ifdef HAVE_uk_syscall_u_time
		ret = uk_syscall_r_u_time((long)usc);
#else /* !HAVE_uk_syscall_u_time */
		ret = uk_syscall_r_time(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_time */

		break;

#endif /* HAVE_uk_syscall_time */

#ifdef HAVE_uk_syscall_setitimer
	case SYS_setitimer:

#ifdef HAVE_uk_syscall_u_setitimer
		ret = uk_syscall_r_u_setitimer((long)usc);
#else /* !HAVE_uk_syscall_u_setitimer */
		ret = uk_syscall_r_setitimer(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_setitimer */

		break;

#endif /* HAVE_uk_syscall_setitimer */

#ifdef HAVE_uk_syscall_timer_create
	case SYS_timer_create:

#ifdef HAVE_uk_syscall_u_timer_create
		ret = uk_syscall_r_u_timer_create((long)usc);
#else /* !HAVE_uk_syscall_u_timer_create */
		ret = uk_syscall_r_timer_create(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_timer_create */

		break;

#endif /* HAVE_uk_syscall_timer_create */

#ifdef HAVE_uk_syscall_timer_delete
	case SYS_timer_delete:

#ifdef HAVE_uk_syscall_u_timer_delete
		ret = uk_syscall_r_u_timer_delete((long)usc);
#else /* !HAVE_uk_syscall_u_timer_delete */
		ret = uk_syscall_r_timer_delete(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_timer_delete */

		break;

#endif /* HAVE_uk_syscall_timer_delete */

#ifdef HAVE_uk_syscall_timer_settime
	case SYS_timer_settime:

#ifdef HAVE_uk_syscall_u_timer_settime
		ret = uk_syscall_r_u_timer_settime((long)usc);
#else /* !HAVE_uk_syscall_u_timer_settime */
		ret = uk_syscall_r_timer_settime(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_timer_settime */

		break;

#endif /* HAVE_uk_syscall_timer_settime */

#ifdef HAVE_uk_syscall_timer_gettime
	case SYS_timer_gettime:

#ifdef HAVE_uk_syscall_u_timer_gettime
		ret = uk_syscall_r_u_timer_gettime((long)usc);
#else /* !HAVE_uk_syscall_u_timer_gettime */
		ret = uk_syscall_r_timer_gettime(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_timer_gettime */

		break;

#endif /* HAVE_uk_syscall_timer_gettime */

#ifdef HAVE_uk_syscall_timer_getoverrun
	case SYS_timer_getoverrun:

#ifdef HAVE_uk_syscall_u_timer_getoverrun
		ret = uk_syscall_r_u_timer_getoverrun((long)usc);
#else /* !HAVE_uk_syscall_u_timer_getoverrun */
		ret = uk_syscall_r_timer_getoverrun(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_timer_getoverrun */

		break;

#endif /* HAVE_uk_syscall_timer_getoverrun */

#ifdef HAVE_uk_syscall_readlink
	case SYS_readlink:

#ifdef HAVE_uk_syscall_u_readlink
		ret = uk_syscall_r_u_readlink((long)usc);
#else /* !HAVE_uk_syscall_u_readlink */
		ret = uk_syscall_r_readlink(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_readlink */

		break;

#endif /* HAVE_uk_syscall_readlink */

#ifdef HAVE_uk_syscall_link
	case SYS_link:

#ifdef HAVE_uk_syscall_u_link
		ret = uk_syscall_r_u_link((long)usc);
#else /* !HAVE_uk_syscall_u_link */
		ret = uk_syscall_r_link(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_link */

		break;

#endif /* HAVE_uk_syscall_link */

#ifdef HAVE_uk_syscall_ftruncate
	case SYS_ftruncate:

#ifdef HAVE_uk_syscall_u_ftruncate
		ret = uk_syscall_r_u_ftruncate((long)usc);
#else /* !HAVE_uk_syscall_u_ftruncate */
		ret = uk_syscall_r_ftruncate(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_ftruncate */

		break;

#endif /* HAVE_uk_syscall_ftruncate */

#ifdef HAVE_uk_syscall_truncate
	case SYS_truncate:

#ifdef HAVE_uk_syscall_u_truncate
		ret = uk_syscall_r_u_truncate((long)usc);
#else /* !HAVE_uk_syscall_u_truncate */
		ret = uk_syscall_r_truncate(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_truncate */

		break;

#endif /* HAVE_uk_syscall_truncate */

#ifdef HAVE_uk_syscall_access
	case SYS_access:

#ifdef HAVE_uk_syscall_u_access
		ret = uk_syscall_r_u_access((long)usc);
#else /* !HAVE_uk_syscall_u_access */
		ret = uk_syscall_r_access(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_access */

		break;

#endif /* HAVE_uk_syscall_access */

#ifdef HAVE_uk_syscall_faccessat
	case SYS_faccessat:

#ifdef HAVE_uk_syscall_u_faccessat
		ret = uk_syscall_r_u_faccessat((long)usc);
#else /* !HAVE_uk_syscall_u_faccessat */
		ret = uk_syscall_r_faccessat(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_faccessat */

		break;

#endif /* HAVE_uk_syscall_faccessat */

#ifdef HAVE_uk_syscall_fallocate
	case SYS_fallocate:

#ifdef HAVE_uk_syscall_u_fallocate
		ret = uk_syscall_r_u_fallocate((long)usc);
#else /* !HAVE_uk_syscall_u_fallocate */
		ret = uk_syscall_r_fallocate(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_fallocate */

		break;

#endif /* HAVE_uk_syscall_fallocate */

#ifdef HAVE_uk_syscall_chdir
	case SYS_chdir:

#ifdef HAVE_uk_syscall_u_chdir
		ret = uk_syscall_r_u_chdir((long)usc);
#else /* !HAVE_uk_syscall_u_chdir */
		ret = uk_syscall_r_chdir(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_chdir */

		break;

#endif /* HAVE_uk_syscall_chdir */

#ifdef HAVE_uk_syscall_fchdir
	case SYS_fchdir:

#ifdef HAVE_uk_syscall_u_fchdir
		ret = uk_syscall_r_u_fchdir((long)usc);
#else /* !HAVE_uk_syscall_u_fchdir */
		ret = uk_syscall_r_fchdir(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_fchdir */

		break;

#endif /* HAVE_uk_syscall_fchdir */

#ifdef HAVE_uk_syscall_chmod
	case SYS_chmod:

#ifdef HAVE_uk_syscall_u_chmod
		ret = uk_syscall_r_u_chmod((long)usc);
#else /* !HAVE_uk_syscall_u_chmod */
		ret = uk_syscall_r_chmod(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_chmod */

		break;

#endif /* HAVE_uk_syscall_chmod */

#ifdef HAVE_uk_syscall_fchmod
	case SYS_fchmod:

#ifdef HAVE_uk_syscall_u_fchmod
		ret = uk_syscall_r_u_fchmod((long)usc);
#else /* !HAVE_uk_syscall_u_fchmod */
		ret = uk_syscall_r_fchmod(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_fchmod */

		break;

#endif /* HAVE_uk_syscall_fchmod */

#ifdef HAVE_uk_syscall_utime
	case SYS_utime:

#ifdef HAVE_uk_syscall_u_utime
		ret = uk_syscall_r_u_utime((long)usc);
#else /* !HAVE_uk_syscall_u_utime */
		ret = uk_syscall_r_utime(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_utime */

		break;

#endif /* HAVE_uk_syscall_utime */

#ifdef HAVE_uk_syscall_utimes
	case SYS_utimes:

#ifdef HAVE_uk_syscall_u_utimes
		ret = uk_syscall_r_u_utimes((long)usc);
#else /* !HAVE_uk_syscall_u_utimes */
		ret = uk_syscall_r_utimes(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_utimes */

		break;

#endif /* HAVE_uk_syscall_utimes */

#ifdef HAVE_uk_syscall_mknod
	case SYS_mknod:

#ifdef HAVE_uk_syscall_u_mknod
		ret = uk_syscall_r_u_mknod((long)usc);
#else /* !HAVE_uk_syscall_u_mknod */
		ret = uk_syscall_r_mknod(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_mknod */

		break;

#endif /* HAVE_uk_syscall_mknod */

#ifdef HAVE_uk_syscall_rmdir
	case SYS_rmdir:

#ifdef HAVE_uk_syscall_u_rmdir
		ret = uk_syscall_r_u_rmdir((long)usc);
#else /* !HAVE_uk_syscall_u_rmdir */
		ret = uk_syscall_r_rmdir(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_rmdir */

		break;

#endif /* HAVE_uk_syscall_rmdir */

#ifdef HAVE_uk_syscall_rename
	case SYS_rename:

#ifdef HAVE_uk_syscall_u_rename
		ret = uk_syscall_r_u_rename((long)usc);
#else /* !HAVE_uk_syscall_u_rename */
		ret = uk_syscall_r_rename(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_rename */

		break;

#endif /* HAVE_uk_syscall_rename */

#ifdef HAVE_uk_syscall_fsync
	case SYS_fsync:

#ifdef HAVE_uk_syscall_u_fsync
		ret = uk_syscall_r_u_fsync((long)usc);
#else /* !HAVE_uk_syscall_u_fsync */
		ret = uk_syscall_r_fsync(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_fsync */

		break;

#endif /* HAVE_uk_syscall_fsync */

#ifdef HAVE_uk_syscall_fdatasync
	case SYS_fdatasync:

#ifdef HAVE_uk_syscall_u_fdatasync
		ret = uk_syscall_r_u_fdatasync((long)usc);
#else /* !HAVE_uk_syscall_u_fdatasync */
		ret = uk_syscall_r_fdatasync(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_fdatasync */

		break;

#endif /* HAVE_uk_syscall_fdatasync */

#ifdef HAVE_uk_syscall_umask
	case SYS_umask:

#ifdef HAVE_uk_syscall_u_umask
		ret = uk_syscall_r_u_umask((long)usc);
#else /* !HAVE_uk_syscall_u_umask */
		ret = uk_syscall_r_umask(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_umask */

		break;

#endif /* HAVE_uk_syscall_umask */

#ifdef HAVE_uk_syscall_lstat
	case SYS_lstat:

#ifdef HAVE_uk_syscall_u_lstat
		ret = uk_syscall_r_u_lstat((long)usc);
#else /* !HAVE_uk_syscall_u_lstat */
		ret = uk_syscall_r_lstat(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_lstat */

		break;

#endif /* HAVE_uk_syscall_lstat */

#ifdef HAVE_uk_syscall_flock
	case SYS_flock:

#ifdef HAVE_uk_syscall_u_flock
		ret = uk_syscall_r_u_flock((long)usc);
#else /* !HAVE_uk_syscall_u_flock */
		ret = uk_syscall_r_flock(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_flock */

		break;

#endif /* HAVE_uk_syscall_flock */

#ifdef HAVE_uk_syscall_getcwd
	case SYS_getcwd:

#ifdef HAVE_uk_syscall_u_getcwd
		ret = uk_syscall_r_u_getcwd((long)usc);
#else /* !HAVE_uk_syscall_u_getcwd */
		ret = uk_syscall_r_getcwd(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_getcwd */

		break;

#endif /* HAVE_uk_syscall_getcwd */

#ifdef HAVE_uk_syscall_utimensat
	case SYS_utimensat:

#ifdef HAVE_uk_syscall_u_utimensat
		ret = uk_syscall_r_u_utimensat((long)usc);
#else /* !HAVE_uk_syscall_u_utimensat */
		ret = uk_syscall_r_utimensat(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_utimensat */

		break;

#endif /* HAVE_uk_syscall_utimensat */

#ifdef HAVE_uk_syscall_futimesat
	case SYS_futimesat:

#ifdef HAVE_uk_syscall_u_futimesat
		ret = uk_syscall_r_u_futimesat((long)usc);
#else /* !HAVE_uk_syscall_u_futimesat */
		ret = uk_syscall_r_futimesat(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_futimesat */

		break;

#endif /* HAVE_uk_syscall_futimesat */

#ifdef HAVE_uk_syscall_sync
	case SYS_sync:

#ifdef HAVE_uk_syscall_u_sync
		ret = uk_syscall_r_u_sync((long)usc);
#else /* !HAVE_uk_syscall_u_sync */
		ret = uk_syscall_r_sync(
					);

#endif /* !HAVE_uk_syscall_u_sync */

		break;

#endif /* HAVE_uk_syscall_sync */

#ifdef HAVE_uk_syscall_mount
	case SYS_mount:

#ifdef HAVE_uk_syscall_u_mount
		ret = uk_syscall_r_u_mount((long)usc);
#else /* !HAVE_uk_syscall_u_mount */
		ret = uk_syscall_r_mount(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3, usc->regs.rarg4);

#endif /* !HAVE_uk_syscall_u_mount */

		break;

#endif /* HAVE_uk_syscall_mount */

#ifdef HAVE_uk_syscall_statfs
	case SYS_statfs:

#ifdef HAVE_uk_syscall_u_statfs
		ret = uk_syscall_r_u_statfs((long)usc);
#else /* !HAVE_uk_syscall_u_statfs */
		ret = uk_syscall_r_statfs(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_statfs */

		break;

#endif /* HAVE_uk_syscall_statfs */

#ifdef HAVE_uk_syscall_fstatfs
	case SYS_fstatfs:

#ifdef HAVE_uk_syscall_u_fstatfs
		ret = uk_syscall_r_u_fstatfs((long)usc);
#else /* !HAVE_uk_syscall_u_fstatfs */
		ret = uk_syscall_r_fstatfs(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_fstatfs */

		break;

#endif /* HAVE_uk_syscall_fstatfs */

#ifdef HAVE_uk_syscall_fchown
	case SYS_fchown:

#ifdef HAVE_uk_syscall_u_fchown
		ret = uk_syscall_r_u_fchown((long)usc);
#else /* !HAVE_uk_syscall_u_fchown */
		ret = uk_syscall_r_fchown(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_fchown */

		break;

#endif /* HAVE_uk_syscall_fchown */

#ifdef HAVE_uk_syscall_lchown
	case SYS_lchown:

#ifdef HAVE_uk_syscall_u_lchown
		ret = uk_syscall_r_u_lchown((long)usc);
#else /* !HAVE_uk_syscall_u_lchown */
		ret = uk_syscall_r_lchown(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_lchown */

		break;

#endif /* HAVE_uk_syscall_lchown */

#ifdef HAVE_uk_syscall_chown
	case SYS_chown:

#ifdef HAVE_uk_syscall_u_chown
		ret = uk_syscall_r_u_chown((long)usc);
#else /* !HAVE_uk_syscall_u_chown */
		ret = uk_syscall_r_chown(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_chown */

		break;

#endif /* HAVE_uk_syscall_chown */

#ifdef HAVE_uk_syscall_stat
	case SYS_stat:

#ifdef HAVE_uk_syscall_u_stat
		ret = uk_syscall_r_u_stat((long)usc);
#else /* !HAVE_uk_syscall_u_stat */
		ret = uk_syscall_r_stat(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_stat */

		break;

#endif /* HAVE_uk_syscall_stat */

#ifdef HAVE_uk_syscall_mkdir
	case SYS_mkdir:

#ifdef HAVE_uk_syscall_u_mkdir
		ret = uk_syscall_r_u_mkdir((long)usc);
#else /* !HAVE_uk_syscall_u_mkdir */
		ret = uk_syscall_r_mkdir(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_mkdir */

		break;

#endif /* HAVE_uk_syscall_mkdir */

#ifdef HAVE_uk_syscall_mkdirat
	case SYS_mkdirat:

#ifdef HAVE_uk_syscall_u_mkdirat
		ret = uk_syscall_r_u_mkdirat((long)usc);
#else /* !HAVE_uk_syscall_u_mkdirat */
		ret = uk_syscall_r_mkdirat(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_mkdirat */

		break;

#endif /* HAVE_uk_syscall_mkdirat */

#ifdef HAVE_uk_syscall_umount2
	case SYS_umount2:

#ifdef HAVE_uk_syscall_u_umount2
		ret = uk_syscall_r_u_umount2((long)usc);
#else /* !HAVE_uk_syscall_u_umount2 */
		ret = uk_syscall_r_umount2(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_umount2 */

		break;

#endif /* HAVE_uk_syscall_umount2 */

#ifdef HAVE_uk_syscall_symlink
	case SYS_symlink:

#ifdef HAVE_uk_syscall_u_symlink
		ret = uk_syscall_r_u_symlink((long)usc);
#else /* !HAVE_uk_syscall_u_symlink */
		ret = uk_syscall_r_symlink(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_symlink */

		break;

#endif /* HAVE_uk_syscall_symlink */

#ifdef HAVE_uk_syscall_unlink
	case SYS_unlink:

#ifdef HAVE_uk_syscall_u_unlink
		ret = uk_syscall_r_u_unlink((long)usc);
#else /* !HAVE_uk_syscall_u_unlink */
		ret = uk_syscall_r_unlink(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_unlink */

		break;

#endif /* HAVE_uk_syscall_unlink */

#ifdef HAVE_uk_syscall_unlinkat
	case SYS_unlinkat:

#ifdef HAVE_uk_syscall_u_unlinkat
		ret = uk_syscall_r_u_unlinkat((long)usc);
#else /* !HAVE_uk_syscall_u_unlinkat */
		ret = uk_syscall_r_unlinkat(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_unlinkat */

		break;

#endif /* HAVE_uk_syscall_unlinkat */

#ifdef HAVE_uk_syscall_chroot
	case SYS_chroot:

#ifdef HAVE_uk_syscall_u_chroot
		ret = uk_syscall_r_u_chroot((long)usc);
#else /* !HAVE_uk_syscall_u_chroot */
		ret = uk_syscall_r_chroot(
					usc->regs.rarg0);

#endif /* !HAVE_uk_syscall_u_chroot */

		break;

#endif /* HAVE_uk_syscall_chroot */

#ifdef HAVE_uk_syscall_getdents64
	case SYS_getdents64:

#ifdef HAVE_uk_syscall_u_getdents64
		ret = uk_syscall_r_u_getdents64((long)usc);
#else /* !HAVE_uk_syscall_u_getdents64 */
		ret = uk_syscall_r_getdents64(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_getdents64 */

		break;

#endif /* HAVE_uk_syscall_getdents64 */

#ifdef HAVE_uk_syscall_newfstatat
	case SYS_newfstatat:

#ifdef HAVE_uk_syscall_u_newfstatat
		ret = uk_syscall_r_u_newfstatat((long)usc);
#else /* !HAVE_uk_syscall_u_newfstatat */
		ret = uk_syscall_r_newfstatat(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_newfstatat */

		break;

#endif /* HAVE_uk_syscall_newfstatat */

#ifdef HAVE_uk_syscall_open
	case SYS_open:

#ifdef HAVE_uk_syscall_u_open
		ret = uk_syscall_r_u_open((long)usc);
#else /* !HAVE_uk_syscall_u_open */
		ret = uk_syscall_r_open(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_open */

		break;

#endif /* HAVE_uk_syscall_open */

#ifdef HAVE_uk_syscall_openat
	case SYS_openat:

#ifdef HAVE_uk_syscall_u_openat
		ret = uk_syscall_r_u_openat((long)usc);
#else /* !HAVE_uk_syscall_u_openat */
		ret = uk_syscall_r_openat(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2, usc->regs.rarg3);

#endif /* !HAVE_uk_syscall_u_openat */

		break;

#endif /* HAVE_uk_syscall_openat */

#ifdef HAVE_uk_syscall_creat
	case SYS_creat:

#ifdef HAVE_uk_syscall_u_creat
		ret = uk_syscall_r_u_creat((long)usc);
#else /* !HAVE_uk_syscall_u_creat */
		ret = uk_syscall_r_creat(
					usc->regs.rarg0, usc->regs.rarg1);

#endif /* !HAVE_uk_syscall_u_creat */

		break;

#endif /* HAVE_uk_syscall_creat */

#ifdef HAVE_uk_syscall_getrandom
	case SYS_getrandom:

#ifdef HAVE_uk_syscall_u_getrandom
		ret = uk_syscall_r_u_getrandom((long)usc);
#else /* !HAVE_uk_syscall_u_getrandom */
		ret = uk_syscall_r_getrandom(
					usc->regs.rarg0, usc->regs.rarg1, usc->regs.rarg2);

#endif /* !HAVE_uk_syscall_u_getrandom */

		break;

#endif /* HAVE_uk_syscall_getrandom */
	default:
		uk_pr_debug("syscall \"%s\" is not available\n", uk_syscall_name(usc->regs.rsyscall));
		ret = -ENOSYS;
	}
	return ret;
}

