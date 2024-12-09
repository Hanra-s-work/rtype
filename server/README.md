------ UTILISATION DU SERVEUR -----

sudo apt update
sudo apt install libasio-dev

----- PROTOCOL UDP | COMMUNICATION SERVEUR / CLIENT -----

1. Format des messages binaires

Chaque message échangé entre le client et le serveur suit un format précis. Un paquet binaire est structuré de la manière suivante :

    Type du message (1 octet) : Un identifiant indiquant le type d'action (par exemple : MOVE, SHOOT, etc.).
    Taille du message (2 octets) : La taille du payload (contenu) du message.
    Payload : Les données associées à l'action (par exemple, la direction d’un mouvement ou un code d’erreur).

2. Types de messages que le serveur attend et envoie
Types de messages envoyés par le client au serveur :

    - CONNECT (0x01)
        Description : Le client se connecte au serveur.
        Format :

    0x01 0x00 0x08 username

        username est le nom du joueur (ex: "Player1").

    - DISCONNECT (0x02)

        Description : Le client se déconnecte du serveur.
        Format :

        0x02 0x00 0x00

    - MOVE (0x03)

        Description : Le joueur se déplace.
        Format :

        0x03 0x00 0x01 0x01

        Payload : 0x01 pour "UP", 0x02 pour "DOWN", 0x03 pour "LEFT", 0x04 pour "RIGHT".

    - SHOOT (0x04)

        Description : Le joueur tire.
        Format :

        0x04 0x00 0x02 0x01 0x02

        Payload : 0x01 0x02 (par exemple, pour un angle de tir en coordonnées binaires).

    - SPAWN (0x05)

        Description : Apparition d’un ennemi ou d’un objet dans le jeu.
        Format :

        0x05 0x00 0x04 0x01 0x0A 0x14 0x02

        Payload : [ID, x, y, type] de l'entité à spawner.

    - UPDATE (0x06)

        Description : Le serveur envoie les informations actualisées sur l'état du jeu.
        Format :

        0x06 0x00 0x08 0x01 0x0A 0x14 0x02 0x02 0x1E 0x28

        Payload : Une liste d’entités (joueurs, ennemis) avec leur position (x, y) et leur type.

3. Gestion des erreurs
Erreurs envoyées par le client au serveur

Le client (GUI) peut rencontrer des erreurs, comme par exemple si une action est invalide ou si des conditions de jeu ne sont pas respectées (par exemple, essayer de déplacer un joueur en dehors des limites du terrain). Dans ce cas, le client doit envoyer une erreur au serveur sous forme binaire pour signaler le problème.

Exemple d'un message d'erreur : Si un joueur essaie d'effectuer une action invalide, le client peut envoyer une erreur comme ceci :

0xFF 0x00 0x01 0x01  // Type: ERREUR, Taille: 1, Payload: 0x01 (erreur pour déplacement invalide)

Erreurs envoyées par le serveur au client

Le serveur peut également envoyer des erreurs au client, par exemple :

    Paquets malformés reçus du client.
    Erreurs lors de l'exécution des actions du client.

Le serveur envoie un message d'erreur structuré sous forme binaire avec un type de message 0xFF. Exemple d'un message d'erreur renvoyé par le serveur :

0xFF 0x00 0x02 0x00 0x01  // Type: ERREUR, Taille: 2, Payload: 0x00 0x01 (erreur pour paquet malformé)

4. Exemple d'utilisation
Côté Client :

    Déplacer un joueur vers le haut :
        Le client envoie un paquet de type MOVE avec la direction vers le haut.
        Message : 0x03 0x00 0x01 0x01.

    Tirer un projectile :
        Le client envoie un paquet de type SHOOT avec les coordonnées de l'angle.
        Message : 0x04 0x00 0x02 0x01 0x02.

Côté Serveur :

    Mise à jour des positions des entités :
        Le serveur envoie un paquet de type UPDATE pour informer les clients des positions actualisées des joueurs et des ennemis.
        Message : 0x06 0x00 0x08 0x01 0x0A 0x14 0x02 0x02 0x1E 0x28.

    Réponse d'erreur du serveur :
        Si un paquet malformé est reçu, le serveur envoie un message d’erreur.
        Message : 0xFF 0x00 0x02 0x00 0x01.