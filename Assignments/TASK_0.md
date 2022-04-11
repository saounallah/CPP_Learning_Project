# Se familiariser avec l'existant

## A- Exécution

Compilez et lancez le programme.

Allez dans le fichier `tower_sim.cpp` et recherchez la fonction responsable de gérer les inputs du programme.

<br>-->void TowerSimulation::create_keystrokes() const</br>

Sur quelle touche faut-il appuyer pour ajouter un avion ?
<br>-->sur la touche 'c'</br>

Comment faire pour quitter le programme ?
<br>-->appuez sur la touche 'x' ou 'q'</br>

A quoi sert la touche 'F' ?
<br>--> mettre en 'plein ecran' l'application</br>

Ajoutez un avion à la simulation et attendez.
Que est le comportement de l'avion ?
<br>--> l'avion vol, tourne et atteri à l'infini</br>

Quelles informations s'affichent dans la console ?
<br>-->le numéro de l'avion</br>
<br>-->les actions de l'avion : is now landing, now servicing, done servicing, lift off</br>

Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?
<br>-->chaque avion essaye de s'atterir mais pas au même endroit ou au meme moment, ils font les actions.</br>    

## B- Analyse du code

Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.
<br>--> **Aircraft** : représente les movements de l'avion, a comme rôle de l'affichage de l'avion dans l'application</br>  
<br>--> **AircraftType** : représente les caractéristiques de chaque type d'avion (y'a 3 types)</br>  
<br>--> **Airport** : cette classe représente l'affichage de l'aéoropot, la reservation  du terminal et le mouvement à l'aéroport  </br>  
<br>--> **AirportType** : représente les différents élément de l'aéorport, la position du passage, la position du passerelle, la position du terminal et la piste</br> 
<br>--> **Point2D** : représente les points en 2D</br>   
<br>--> **Point3D** :  représente les points en 3D?</br>  
<br>--> **Runway** : représente la piste </br>  
<br>--> **Terminal** : représente deux opérations de l'avion "now serving" et "done servicing" qui doit l'effectuer </br>
<br>--> **Tower** : représente le tour de controle de l'aeroport qui produire les instructions pour l'avion</br>
<br>--> **TowerSimulation** : permet d'initialiser l'aéroport et affecter ses actions </br>
<br>--> **Waypoint** : représente un ENUM indique si le waypoint est wp_air, wp_ground ou wp_terminal</br>

Pour les classes `Tower`, `Aircaft`, `Airport` et `Terminal`, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent.
Réalisez ensuite un schéma présentant comment ces différentes classes intéragissent ensemble.

<br>--> **Tower** : </br>
<ul>
    <li>WaypointQueue Tower::get_circle() const : retourne un ensemble de waypoint de dimension 3d de type wp_air</li>
    <li>WaypointQueue Tower::get_instructions(Aircraft& aircraft) : récupère les instructions d'un avion en fonction de sa position actuelle</li>
    <li>void Tower::arrived_at_terminal(const Aircraft& aircraft) : signale qu'un avion est arrivé au terminal et commence son service</li>
</ul>

<br>--> **Aircaft** : </br>
<ul>
    <li>const std::string& get_flight_num() const : récupère le numéro de vol </li>
    <li>float distance_to(const Point3D& p) const : calculer la distance entre un point donnée et un avion</li>
    <li>void display() const : affichage de l'avion</li>
    <li>void Aircraft::move() : l'avion de déplace jusqu'au prochain waypoint disponible</li>
</ul>
<br>--> **Airport** : </br>
<ul>
    <li>Tower& get_tower() : récupère la tour du contrôle</li>
    <li>void display() const : affichage de l'aéoroprt</li>
    <li>void move() : placement de l'aéroport.</li>
</ul>
<br>--> **Terminal** : </br>
<ul>
    <li>bool in_use() const : permet de savoir si le terminal est utilisé par un avion </li>
    <li>bool is_servicing() const : permet de savoir si un embarquement ou déparquement en cours </li>
    <li>void assign_craft(const Aircraft& aircraft) : assign un avion à un terminal</li>
    <li>void start_service(const Aircraft& aircraft) : démarre le service d'un avion</li>
    <li>void finish_service() : termine le service de l'avion au terminal </li>
    <li>void move() : actualiser le plateau</li>
</ul>

Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ?
<br>--> Tower -> get_instructions</br>   
<br>--> waypoint</br>   
Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?
Expliquez les intérêts de ce choix.
<br>le contenur de la librairie standard choisi pour représenter le chemin est deque. il estvplus efficace pout l'insertion et la suppression d'éléments</br>

## C- Bidouillons !

1) Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion.
Le Concorde est censé pouvoir voler plus vite que les autres avions.
Modifiez le programme pour tenir compte de cela.

2) Identifiez quelle variable contrôle le framerate de la simulation.
Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur.
Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ?\
<br>quand je met le ticks_per_sec = 0, le programme s'arrête car y aura une division par 0</br>
Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en pause, et qui ne passe pas par le framerate.

3) Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.
<br>constexpr unsigned int SERVICE_CYCLES dans config.hpp</br>

4) Lorsqu'un avion a décollé, il réattérit peu de temps après.
Faites en sorte qu'à la place, il soit retiré du programme.\
Indices :\
A quel endroit pouvez-vous savoir que l'avion doit être supprimé ?\
Pourquoi n'est-il pas sûr de procéder au retrait de l'avion dans cette fonction ?
A quel endroit de la callstack pourriez-vous le faire à la place ?\
Que devez-vous modifier pour transmettre l'information de la première à la seconde fonction ?
<br>On peut savoir que l'avion doit être supprimer quand il possède plus de waypoint et qu'il a déja atteri</br>
<br>Dans la classe Tower.cpp dans la fonction get_instructions</br>
<br>La solution est un boolean dans classe Aircraft qui passe a vrai si l'avion veulent s'envoler une deuxième fois.</br>

5) Lorsqu'un objet de type `Displayable` est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher.
Il faut également penser à le supprimer de cette liste avant de le détruire.
Faites en sorte que l'ajout et la suppression de `display_queue` soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit.
Pourquoi n'est-il pas spécialement pertinent d'en faire de même pour `DynamicObject` ?

6) La tour de contrôle a besoin de stocker pour tout `Aircraft` le `Terminal` qui lui est actuellement attribué, afin de pouvoir le libérer une fois que l'avion décolle.
Cette information est actuellement enregistrée dans un `std::vector<std::pair<const Aircraft*, size_t>>` (size_t représentant l'indice du terminal).
Cela fait que la recherche du terminal associé à un avion est réalisée en temps linéaire, par rapport au nombre total de terminaux.
Cela n'est pas grave tant que ce nombre est petit, mais pour préparer l'avenir, on aimerait bien remplacer le vector par un conteneur qui garantira des opérations efficaces, même s'il y a beaucoup de terminaux.\
Modifiez le code afin d'utiliser un conteneur STL plus adapté. Normalement, à la fin, la fonction `find_craft_and_terminal(const Aicraft&)` ne devrait plus être nécessaire.

## D- Théorie

1) Comment a-t-on fait pour que seule la classe `Tower` puisse réserver un terminal de l'aéroport ?

2) En regardant le contenu de la fonction `void Aircraft::turn(Point3D direction)`, pourquoi selon-vous ne sommes-nous pas passer par une réference ?
Pensez-vous qu'il soit possible d'éviter la copie du `Point3D` passé en paramètre ?

## E- Bonus

Le temps qui s'écoule dans la simulation dépend du framerate du programme.
La fonction move() n'utilise pas le vrai temps. Faites en sorte que si.
Par conséquent, lorsque vous augmentez le framerate, la simulation s'exécute plus rapidement, et si vous le diminuez, celle-ci s'exécute plus lentement.

Dans la plupart des jeux ou logiciels que vous utilisez, lorsque le framerate diminue, vous ne le ressentez quasiment pas (en tout cas, tant que celui-ci ne diminue pas trop).
Pour avoir ce type de résultat, les fonctions d'update prennent généralement en paramètre le temps qui s'est écoulé depuis la dernière frame, et l'utilise pour calculer le mouvement des entités.

Recherchez sur Internet comment obtenir le temps courant en C++ et arrangez-vous pour calculer le dt (delta time) qui s'écoule entre deux frames.
Lorsque le programme tourne bien, celui-ci devrait être quasiment égale à 1/framerate.
Cependant, si le programme se met à ramer et que la callback de glutTimerFunc est appelée en retard (oui oui, c'est possible), alors votre dt devrait être supérieur à 1/framerate.

Passez ensuite cette valeur à la fonction `move` des `DynamicObject`, et utilisez-la pour calculer les nouvelles positions de chaque avion.
Vérifiez maintenant en exécutant le programme que, lorsque augmentez le framerate du programme, vous n'augmentez pas la vitesse de la simulation.

Ajoutez ensuite deux nouveaux inputs permettant d'accélérer ou de ralentir la simulation.
