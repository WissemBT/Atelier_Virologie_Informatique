#include <linux/unistd.h>
#define STR( str ) \
({ char* var = 0 ; \
asm volatile ( "call .After_string%=\n" \
".string \""str"\"\n" \
".byte 0 \n" \
".After_string%=:\n" \
"\tpop %0\n" \
: "=m" ( var ) ) ; \
var ; })
int strlen(char *s) // Taille d'une chaîne de caractères
{
int len=0;
while (s[len]) len++;
return len;
}
// Conversion d'un nombre non signé en une chaîne de caractères en décimal
void utoa(int n, char *s)
{
int i,j;
char t[16];
i = 0;
do {
t[i++] = n % 10 + '0';
} while ((n /= 10) > 0);
for(j=i-1;j>=0;j--)
s[i-j-1]=t[j];
s[i] = '\0';
}
// Conversion d'un nombre non signé en une chaîne de caractères en hexadécimal
void xtoa(int n, char *s)
{
int temp=n, i=0, j;
char m[16];
while (temp>0)
{
m[i]=temp%16;
if(m[i]>9) m[i]+=55;
else m[i]+='0';
temp=temp/16;
i++;
}
for (j=i-1;j>=0;j--)
s[i-j-1]=m[j];
s[i] = '\0';
}

void _start()
{
__asm__ volatile ("call main");
}

static inline long long syscall3(long long syscallnum, long long arg0, long long arg1, long
long arg2)
{
register long long syscallnum_ __asm__("rax");
register long long arg0_ __asm__("rdi");
register long long arg1_ __asm__("rsi");
register long long arg2_ __asm__("rdx");
syscallnum_ = syscallnum;
arg0_ = arg0;
arg1_ = arg1;
arg2_ = arg2;
asm volatile
(
"syscall"
: "+r"(syscallnum_)
: "r"(arg0_), "r"(arg1_), "r"(arg2_)
);
return syscallnum_;
}

static long long write(int fd, const void *buf, int count)
{
return syscall3(__NR_write, fd, (long long)buf, count);
}

static inline long long syscall1(long long syscallnum, long long arg0)
{
    register long long syscallnum_ __asm__("rax");
    register long long arg0_ __asm__("rdi");
    syscallnum_ = syscallnum;
    arg0_ = arg0;
    asm volatile
    (
        "syscall"
        : "+r"(syscallnum_)
        : "r"(arg0_)
    );
    return syscallnum_;
}

static long long exit(int arg){
	syscall1(__NR_exit, arg);
}
void End();
void main() {
    int SizeOfInjectedCode = End - _start;
    char ToBePrinted[20];
    utoa(SizeOfInjectedCode,ToBePrinted);   
    write(1,STR("Hello, World!\\r\\n") , 15);
    write(1,STR("Taille du code est : "),21);
    write(1,ToBePrinted,strlen(ToBePrinted));
    exit(0);
}

void End() {}
