/*
 * Generated by dtrace(1M).
 */

#ifndef	_DTRACE_H
#define	_DTRACE_H

#include <unistd.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define RUBY_STABILITY "___dtrace_stability$ruby$v1$5_5_5_1_1_5_1_1_5_5_5_5_5_5_5"

#define RUBY_TYPEDEFS "___dtrace_typedefs$ruby$v2"

#define	RUBY_FUNCTION_ENTRY(arg0, arg1, arg2, arg3) \
{ \
	__asm__ volatile(".reference " RUBY_TYPEDEFS); \
	__dtrace_probe$ruby$function__entry$v1$63686172202a$63686172202a$63686172202a$696e74(arg0, arg1, arg2, arg3); \
	__asm__ volatile(".reference " RUBY_STABILITY); \
} 
#define	RUBY_FUNCTION_ENTRY_ENABLED() \
	__dtrace_isenabled$ruby$function__entry$v1()
#define	RUBY_FUNCTION_RETURN(arg0, arg1, arg2, arg3) \
{ \
	__asm__ volatile(".reference " RUBY_TYPEDEFS); \
	__dtrace_probe$ruby$function__return$v1$63686172202a$63686172202a$63686172202a$696e74(arg0, arg1, arg2, arg3); \
	__asm__ volatile(".reference " RUBY_STABILITY); \
} 
#define	RUBY_FUNCTION_RETURN_ENABLED() \
	__dtrace_isenabled$ruby$function__return$v1()
#define	RUBY_GC_BEGIN() \
{ \
	__asm__ volatile(".reference " RUBY_TYPEDEFS); \
	__dtrace_probe$ruby$gc__begin$v1(); \
	__asm__ volatile(".reference " RUBY_STABILITY); \
} 
#define	RUBY_GC_BEGIN_ENABLED() \
	__dtrace_isenabled$ruby$gc__begin$v1()
#define	RUBY_GC_END() \
{ \
	__asm__ volatile(".reference " RUBY_TYPEDEFS); \
	__dtrace_probe$ruby$gc__end$v1(); \
	__asm__ volatile(".reference " RUBY_STABILITY); \
} 
#define	RUBY_GC_END_ENABLED() \
	__dtrace_isenabled$ruby$gc__end$v1()
#define	RUBY_LINE(arg0, arg1) \
{ \
	__asm__ volatile(".reference " RUBY_TYPEDEFS); \
	__dtrace_probe$ruby$line$v1$63686172202a$696e74(arg0, arg1); \
	__asm__ volatile(".reference " RUBY_STABILITY); \
} 
#define	RUBY_LINE_ENABLED() \
	__dtrace_isenabled$ruby$line$v1()
#define	RUBY_OBJECT_CREATE_DONE(arg0, arg1, arg2) \
{ \
	__asm__ volatile(".reference " RUBY_TYPEDEFS); \
	__dtrace_probe$ruby$object__create__done$v1$63686172202a$63686172202a$696e74(arg0, arg1, arg2); \
	__asm__ volatile(".reference " RUBY_STABILITY); \
} 
#define	RUBY_OBJECT_CREATE_DONE_ENABLED() \
	__dtrace_isenabled$ruby$object__create__done$v1()
#define	RUBY_OBJECT_CREATE_START(arg0, arg1, arg2) \
{ \
	__asm__ volatile(".reference " RUBY_TYPEDEFS); \
	__dtrace_probe$ruby$object__create__start$v1$63686172202a$63686172202a$696e74(arg0, arg1, arg2); \
	__asm__ volatile(".reference " RUBY_STABILITY); \
} 
#define	RUBY_OBJECT_CREATE_START_ENABLED() \
	__dtrace_isenabled$ruby$object__create__start$v1()
#define	RUBY_OBJECT_FREE(arg0) \
{ \
	__asm__ volatile(".reference " RUBY_TYPEDEFS); \
	__dtrace_probe$ruby$object__free$v1$63686172202a(arg0); \
	__asm__ volatile(".reference " RUBY_STABILITY); \
} 
#define	RUBY_OBJECT_FREE_ENABLED() \
	__dtrace_isenabled$ruby$object__free$v1()
#define	RUBY_RAISE(arg0, arg1, arg2) \
{ \
	__asm__ volatile(".reference " RUBY_TYPEDEFS); \
	__dtrace_probe$ruby$raise$v1$63686172202a$63686172202a$696e74(arg0, arg1, arg2); \
	__asm__ volatile(".reference " RUBY_STABILITY); \
} 
#define	RUBY_RAISE_ENABLED() \
	__dtrace_isenabled$ruby$raise$v1()
#define	RUBY_RESCUE(arg0, arg1) \
{ \
	__asm__ volatile(".reference " RUBY_TYPEDEFS); \
	__dtrace_probe$ruby$rescue$v1$63686172202a$696e74(arg0, arg1); \
	__asm__ volatile(".reference " RUBY_STABILITY); \
} 
#define	RUBY_RESCUE_ENABLED() \
	__dtrace_isenabled$ruby$rescue$v1()
#define	RUBY_RUBY_PROBE(arg0, arg1) \
{ \
	__asm__ volatile(".reference " RUBY_TYPEDEFS); \
	__dtrace_probe$ruby$ruby__probe$v1$63686172202a$63686172202a(arg0, arg1); \
	__asm__ volatile(".reference " RUBY_STABILITY); \
} 
#define	RUBY_RUBY_PROBE_ENABLED() \
	__dtrace_isenabled$ruby$ruby__probe$v1()


extern void __dtrace_probe$ruby$function__entry$v1$63686172202a$63686172202a$63686172202a$696e74(char *, char *, char *, int);
extern int __dtrace_isenabled$ruby$function__entry$v1(void);
extern void __dtrace_probe$ruby$function__return$v1$63686172202a$63686172202a$63686172202a$696e74(char *, char *, char *, int);
extern int __dtrace_isenabled$ruby$function__return$v1(void);
extern void __dtrace_probe$ruby$gc__begin$v1(void);
extern int __dtrace_isenabled$ruby$gc__begin$v1(void);
extern void __dtrace_probe$ruby$gc__end$v1(void);
extern int __dtrace_isenabled$ruby$gc__end$v1(void);
extern void __dtrace_probe$ruby$line$v1$63686172202a$696e74(char *, int);
extern int __dtrace_isenabled$ruby$line$v1(void);
extern void __dtrace_probe$ruby$object__create__done$v1$63686172202a$63686172202a$696e74(char *, char *, int);
extern int __dtrace_isenabled$ruby$object__create__done$v1(void);
extern void __dtrace_probe$ruby$object__create__start$v1$63686172202a$63686172202a$696e74(char *, char *, int);
extern int __dtrace_isenabled$ruby$object__create__start$v1(void);
extern void __dtrace_probe$ruby$object__free$v1$63686172202a(char *);
extern int __dtrace_isenabled$ruby$object__free$v1(void);
extern void __dtrace_probe$ruby$raise$v1$63686172202a$63686172202a$696e74(char *, char *, int);
extern int __dtrace_isenabled$ruby$raise$v1(void);
extern void __dtrace_probe$ruby$rescue$v1$63686172202a$696e74(char *, int);
extern int __dtrace_isenabled$ruby$rescue$v1(void);
extern void __dtrace_probe$ruby$ruby__probe$v1$63686172202a$63686172202a(char *, char *);
extern int __dtrace_isenabled$ruby$ruby__probe$v1(void);

#ifdef	__cplusplus
}
#endif

#endif	/* _DTRACE_H */
