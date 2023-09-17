# Atelier_Virologie_Informatique
## Analyse d'un programme C
###i.
done  
###ii.
 done  
###iii
en utilisant command ls -l , on trouve que la taille du fichier résultant helloworld est 16144o.  
###iv.
####file helloworld 
file helloworld
helloworld: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=de57f07fb6ac2be035029808ac694aa6428a1749, for GNU/Linux 3.2.0, not stripped  
####file helloworld.c
helloworld.c: C source, ASCII text  
###v.
Entry point address:               0x10e0  
###vi.
en utilisant la commande readelf -S helloworld, on trouve qu'on a 31 sections.  
###vii.
l'étiquette est _start, et le point d'entrée se trouve au section .text  
###viii.
-_start à l'adresse 0x10e0  
-deregister_tm_clones à l'adresse 0x1110  
-register_tm_clones à l'adresse 0x1140  
-__do_global_dtors_aux à l'adresse 0x1180  
-frame_dummy à l'adresse 0x11c0  
-main à l'adresse 0x11c9  
