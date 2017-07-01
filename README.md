# Kernel-Bidouilles

Ce projet est une série d'exercices pour apprendre le fonctionnement du kernel. 
Il est basé sur Little OS Book : https://github.com/littleosbook/littleosbook
et les tutoriels du OS Dev Wiki : http://wiki.osdev.org

Il est émulable avec Qemu ou Bochs (cf Makefile)

Nécessaires au démarrage :
- boot/loader.s
- boot/linker.ld
- grub

Pour le moment il y a juste un "Hello World" par un accès au port VGA et un log du kernel émulé vers la machine hote dans un fichier par le port série.
La GDT est en place (mode flat, espace d'adressage de : base=0x00000000, limit=0xffffffff) avec 
- un Descripteur NULL
- un Code Segment (privilège 0)
- un Data Segment (privilège 0)
- un Code Segment (privilège 3)
- un Data Segment (privilège 3)

(Readme en cours de rédaction, à venir : les interruptions)
