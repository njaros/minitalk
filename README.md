# minitalk

To translate, go google translator or learn french !

Cette version semble ne plus buguer lors de gestions de signaux UNIX trop fréquent.
Je suppose que le flag SA_RESTART permet de reboot les processus du kernel Darwin qui gère les signaux UNIX quand ils commencent à saturer.
SA_NODEFER est probablement inutile, mais c'est une sécurité au cas où la comparaison entre le precessus kill et -1 est plus long qu'un envoi de signal par ./client

Pas besoin de faire tout ça sur un autre kernel que Darwin (qui n'a pas évolué depuis 2005, vive Apple hahaha).
