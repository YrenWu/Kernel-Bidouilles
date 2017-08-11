# Kernel-Bidouilles

Ce projet est une série d'exercices pour apprendre le fonctionnement des systèmes d'exploitation. 
Il est basé sur Little OS Book : https://github.com/littleosbook/littleosbook
et différentes ressources sur internet

Il est émulable avec Qemu ou Bochs (cf Makefile) et utilise Grub comme bootloader

Nécessaires au démarrage :
- boot/loader.s
- boot/linker.ld
- grub

Pour le moment il y a juste la possibilité d'afficher du texte à l'écran par un accès au port VGA et la possibilité d'écrire un  message du kernel émulé vers la machine hôte dans un fichier en interagissant avec le port série.

La GDT est en place (mode flat, espace d'adressage de : base=0x00000000, limit=0xffffffff) avec 
- un Descripteur NULL
- un Code Segment (privilège 0)
- un Data Segment (privilège 0)
- un Code Segment (privilège 3)
- un Data Segment (privilège 3)

L'IDT est en place avec les exceptions de 0 à 31 


Ressources:
- http://wiki.osdev.org
- http://www.jamesmolloy.co.uk
- http://a.michelizza.free.fr/
