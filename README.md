# Atelier_Virologie_Informatique
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
##Ecriture d'un programme C sans librairie standard
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
