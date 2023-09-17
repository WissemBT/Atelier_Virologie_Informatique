# Atelier_Virologie_Informatique Wissem BEN BETTAIEB
## Analyse d'un programme C
**i.**
done  
**ii.**
 done  
**iii**
en utilisant command ls -l , on trouve que la taille du fichier résultant helloworld est 15968o.  
**iv.** 
file helloworld  
helloworld: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=de57f07fb6ac2be035029808ac694aa6428a1749, for GNU/Linux 3.2.0, not stripped  
file helloworld.c  
helloworld.c: C source, ASCII text  
**v.**
Entry point address:               0x10e0  
**vi.**
en utilisant la commande readelf -S helloworld, on trouve qu'on a 31 sections.  
**vii.**
l'étiquette est _start, et le point d'entrée se trouve au section .text  
**viii.**
-_start à l'adresse 0x10e0  
-deregister_tm_clones à l'adresse 0x1110  
-register_tm_clones à l'adresse 0x1140  
-__do_global_dtors_aux à l'adresse 0x1180  
-frame_dummy à l'adresse 0x11c0  
-main à l'adresse 0x11c9  

## Ecriture d'un programme C sans librairie standard
**ix** done  
**x.a**
'-nostdlib' : Cette option indique au linker de ne pas inclure les bibliothèques standard (comme libc) lors de la création de l'exécutable final. Vous devrez fournir vous-même les fonctions standard ou utiliser des bibliothèques externes.
  
'-fno-builtin' : Cette option indique au compilateur de ne pas supposer que certaines fonctions standard sont intégrées, ce qui signifie qu'il ne doit pas les optimiser comme telles.
  
**x.b**
Les messages d'erreur que nous avons rencontrés indiquent que le linker ne peut pas trouver les implémentations de fonctions telles que open, strlen, write, et close parce que nous avons utilisé -nostdlib, excluant ainsi la bibliothèque standard. Nous devons fournir ces fonctions nous-même pour résoudre ces erreurs.  
**xi**
La directive qui permet d'écrire de l'assembleur dans le programme C est asm volatile.  
La fonction syscall3 est une fonction en C qui facilite l'appel aux appels système en utilisant l'instruction syscall en langage d'assembleur. Elle prend un numéro d'appel système et trois arguments en entrée, puis exécute l'appel système correspondant en utilisant ces valeurs.  
Le numéro d'appel système passé en argument à la fonction syscall3 indique quelle opération système sera effectuée.
  
**xii**
La fonction write est une interface pour l'appel système write. Elle prend un descripteur de fichier (fd), un pointeur vers les données à écrire (buf), et le nombre d'octets à écrire (count) en tant que paramètres. La fonction utilise la fonction syscall3 pour effectuer l'appel système write en passant le numéro d'appel système correspondant __NR_write, le descripteur de fichier, le pointeur vers les données et le nombre d'octets à écrire. Le résultat de l'appel système est renvoyé en tant que valeur de retour de la fonction write.  
**xiii** 
Le message d'avertissement "cannot find entry symbol _start; defaulting to 0000000000001000" signifie que le linker n'a pas trouvé le symbole d'entrée _start dans le programme, et par défaut, il a utilisé l'adresse mémoire par defaut comme point de départ de l'exécution du programme. Cela se produit lorsque le programme ne contient pas explicitement le symbole _start  
**xiv**
il s'agit d'un ficher ELF, lorsque on utilise la commande file hello :  
hello: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=ac70a1787f04e9ae5e08024cbf826c2ccba4364c, not stripped  
**xv**
taille de hello est 13888, or le taille de helloworld est 15968.  
La différence de taille entre les fichiers hello et helloworld s'explique par la manière dont l'appel système write est implémenté dans chacun des fichiers. Le fichier hello utilise  l'assembleur pour effectuer l'appel système, ce qui réduit la taille du fichier exécutable. En revanche, le fichier helloworld  utilise des bibliothèques C standard, ce qui peut entraîner une augmentation de la taille du fichier exécutable en raison de l'inclusion de fonctionnalités supplémentaires de la bibliothèque standard C.  
**xvi** lorsque on fait l'appel ./hello , on obtient un segmentation fault , ce message est attendu parce que on a eu un warning lors de la compilation nous disons que le symbole d'entrée _start n'a été pas trouvé.  
**xvii** _start est le point de départ personnalisé qui utilise l'assembleur pour faire un appelle au main(), permettant à le programme de commencer son exécution.  
**xviii** le message d'erreur est parce que on a pas de fonction exit aprés l'execution de programmes  
**xix**
```
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
```
maintenant, le code fonctionne sans aucun erreur.  
**xx**
hello: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=4624e307a4d844c5d828936f42163acdb64edfe4, not stripped  
**xxi** 
|.ELF............|   
**xxii**
adresse de point d'entrée est  : 0x1000
  
**xxiii**
on trouve 16 sections   
**xxiv**
```
Disassembly of section .text:

0000000000001000 <_start>:
    1000:       f3 0f 1e fa             endbr64
```
on peut aussi verifier qu'il n y a que les fonctions qu'on a écrit jusqu'à maintenant.
## Un premier pas vers l'écriture d'un parasite
**i** Le code indépendant de la position (PIC, Position-Independent Code) est un type de code informatique qui peut être exécuté à n'importe quelle adresse mémoire, sans dépendre d'une adresse mémoire spécifique. Cela signifie que le code peut être chargé en mémoire à différentes adresses, et il fonctionnera toujours correctement, quel que soit l'endroit où il est chargé.  
**ii** Pour créer un code assembleur qui est indépendant de la position (PIC), on peut utiliser quelques techniques tels que :   
1. l'utilisation de registres :  pour stocker et manipuler les données en évitant l'accés directement à la mémoire en utilisant des adresses fixes. 
2. Calcul relatif des adresses : Cela garantit que les adresses sont calculées en fonction de la position actuelle dans le code.
3. Compilation PIC : en gcc '-fpic'
  
**iii**
La macro-fonction STR crée une chaîne de caractères indépendante de la position dans le code assembleur en utilisant une astuce d'assembleur en ligne pour la générer dynamiquement et stocker son adresse dans une variable C. Cela permet d'accéder à la chaîne de caractères de manière flexible, indépendamment de sa position en mémoire.  
**v** 
```
00000000000010a8 <main>:
    10a8:       f3 0f 1e fa             endbr64 
    10ac:       55                      push   rbp
    10ad:       48 89 e5                mov    rbp,rsp
    10b0:       48 83 ec 10             sub    rsp,0x10
    10b4:       48 c7 45 f8 00 00 00    mov    QWORD PTR [rbp-0x8],0x0
    10bb:       00 
    10bc:       e8 11 00 00 00          call   10d2 <.After_string137>
    10c1:       48                      rex.W
    10c2:       65 6c                   gs ins BYTE PTR es:[rdi],dx
    10c4:       6c                      ins    BYTE PTR es:[rdi],dx
    10c5:       6f                      outs   dx,DWORD PTR ds:[rsi]
    10c6:       2c 20                   sub    al,0x20
    10c8:       57                      push   rdi
    10c9:       6f                      outs   dx,DWORD PTR ds:[rsi]
    10ca:       72 6c                   jb     1138 <.After_string137+0x66>
    10cc:       64 21 0d 0a 00 00       and    DWORD PTR fs:[rip+0xffffffff8f00000a],ecx 
```

Le code assembleur généré pour la fonction main() montre que la chaîne de caractères a été créée de manière indépendante de la position. Cela est confirmé par l'instruction call 10d2 <.After_string137>, qui appelle l'adresse .After_string137, où la chaîne de caractères a été générée dynamiquement. Cette approche permet d'obtenir un code indépendant de la position pour la chaîne de caractères, comme souhaité.  
**vi** le programme fonctionne  


