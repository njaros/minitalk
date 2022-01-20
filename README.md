# minitalk

To translate, go google translator or learn french.

Cette version semble ne plus buguer lors d'échanges de signaux UNIX rapide.
Je suppose que le flag SA_RESTART permet de redémarrer les processus qui gère les signaux UNIX quand ils commencent à saturer.
SA_NODEFER est probablement inutile, mais c'est une sécurité au cas où la comparaison entre le precessus kill et -1 est plus long qu'un envoi de signal par ./client.
On peut enlever les sigset et ses fonctions associées, j'ai l'impression que ça ne sert à rien.

Pas besoin de faire tout ça sur un kernel autre que Darwin (qui n'a pas évolué depuis 2005, vive Apple).
