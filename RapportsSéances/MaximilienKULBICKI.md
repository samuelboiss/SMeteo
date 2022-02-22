
# Rapports de séance

## Séance du 01/12 

### Tâches effectuées : 

Lors de cette séance, nous avons fait l’étude du capteur DHT11 (température et humidité) et l’avons mis en marche.
Des tests ont été menés et les résultats obtenus paraissent cohérents. 

Nous avons poursuivi avec le même travail pour le module BMP180 (pression et température). Nous avons dû soudre les pins au module.
Les tests menés ont été satisfaisants. 


### Travail personnel :
-	Recherche sur le fonctionnement du module DHT11 (principe de la thermistance et capteur d’humidité capacitif) et étude de la bibliothèque « DHT Sensor » pour en dégager les fonctions utiles (readHumidity et readTemperature).
-	Soudure de pins sur le module BMP180.
-	Recherche sur le fonctionnement du module BMP180 et étude de la bibliothèque « SFE_BMP180 » pour obtenir les fonctions utiles (startTemp, getTemp, startPressure, getPressure).


## Séance du 15/12 :
### Tâches effectuées :

Lors de cette séance nous avons récupérer l’anémomètre d’un précédent projet (celui de Victor Girard et Benjamin Ferrer) que nous avons démonter pour en connaitre les composants et le fonctionnement. Nos tentatives de mise en marche de l’anémomètre n’étant pas fructueuses, nous l’avons mis de côté et avons débuté l’étude du capteur de luminosité LDR.

Nous avons fait l’étude du capteur LDR (luminosité) et l’avons mis en marche. 
Nous avons mené nos tests dans différentes conditions (plein soleil, ombre, salle de classe) et sommes satisfaits des résultats obtenus. Nous avons à présent pour but de convertir les mesures du capteur en lumens.


### Travail personnel :
-	Recherche sur la Base Shield V2.1 utilisée dans l’anémomètre, permettant de faire le raccord entre la girouette/ anémomètre (utilisant un câble RJ11) et l’arduino via des câbles JST 4P.
-	Etude du code de l’anémomètre pour en comprendre le fonctionnement. L’anémomètre fonctionne grâce à 2 fonctions (meassure() pour la vitesse du vent et  girouette()) créées par les auteurs du projet.
-	Recherche sur la fonction attachInterrupt utilisée pour compter les tours de l’anémomètre. 
-	Recherche sur le module LDR et écriture du code permettant de récupérer une tension variant selon la luminosité de la pièce. 
-	Les tests retournent une valeur (analogique) aux alentours de 900 à l’ombre, 400 en salle de classe et 50 en plein jour.

### Objectifs pour la prochaine séance :

-	Finir la conversion des mesures du capteur LDR en lumens.
-	Adapter le code de l’anémomètre pour nos besoins.

## Séance du 05/01 :
### Tâches effectuées :

Au cours de cette séance, je me suis repenché sur l’anémomètre (de Victor Girard et Benjamin Ferrer) que nous avions mis de côté lors de la dernière séance. 

La documentation de ce projet m’a fait comprendre l’ensemble du montage du boitier et le code utilisé dans l’anémomètre/ girouette. J’ai ainsi repris et modifié ce code afin de le faire fonctionner dans notre projet (suppression de code inutile et adaptation des I/O utilisées). Lors des tests de l’appareil, l’anémomètre renvoie des valeurs (vitesses) satisfaisantes.

Cependant, la girouette était complètement déréglée et renvoyait des directions qui ne collaient pas avec celles de la boussole de mon téléphone. Puisque la girouette renvoie un signal analogique (0-1023) selon sa direction, j’ai arrangé les plages de valeurs pour que la direction de la girouette corresponde à celle de la boussole en orientant initialement l’anémomètre plein ouest.

Une fois l’anémomètre opérationnel, j’ai repris l’étude du capteur LDR et mené des recherches afin de convertir les valeurs renvoyées par celui-ci en lumens. Il s’est avéré qu’établir une échelle en lumens était trop complexe car cela demande d’avoir à disposition différentes sources de lumières dont on connait le flux lumineux et en déduire une relation avec les valeurs du capteur. On se contentera donc d’une échelle « simple » situant la valeur de notre capteur entre « Plein ciel »/ « Ciel nuageux »/ « Ciel obscurci »/ « Nuit ».

## Séance du 12/01 :
### Tâches effectuées :

Lors de cette séance, nous avons rassemblé tous les modules (LDR, DTH11, BMP180, anémomètre, girouette) sur la même carte Arduino et avons mis en commun les codes de chaque module. Ainsi, on est d’ores et déjà en mesure de recueillir un certain nombre de données sur notre Arduino et de les afficher sur le moniteur série. 
Par la suite, nous avons récupéré de nouveaux modules : un module ESP32 pour transmettre les données recueillies par l’Arduino vers notre site web (par Wifi) ; un capteur de radiation ; un capteur PM 2.5 mesurant la qualité de l’air. 
Nous avons commencé l’étude du module ESP32 et du module qualité de l’air. 

Pour le module ESP32, j’ai commencé par étudier sa documentation et notamment l’utilité de chaque pin (GPIO/SPI/I2C) et rechercher un moyen d’écrire/lire des fichiers dans la mémoire flash de l’ESP32. La librairie SPIFFS semble répondre à ce besoin. 

### Travail personnel :
-	Réécriture du code afin de faire fonctionner chaque module ensemble.
-	Montage de tous les capteurs sur une même Arduino.
-	Documentation sur le module ESP32 (pinLayout / bibliothèque Wifi).
-	Ecriture d’un programme afin de tester le fonctionnement de l’ESP32. 
-	Etude de la librairie SPIFFS servant à écrire/lire/modifier des fichiers dans la mémoire flash de l’ESP32. 
-	Ecriture d'un programme permettant de lancer l'ESP32 comme serveur.


## Pause pédagogique du 24/01 au 30/01 :
Tout au long de la pause pédagogique, j’ai cherché à ajouter notre fichier HTML au module ESP32 et faire le pont entre celui-ci et l’Atmel328 pour l’échange de données. 
Dans un premier temps, j’ai exploré les exemples proposés par l’IDE d’Arduino pour voir les utilisations du module ESP32. Dans la catégorie « WebServer », l’exemple de « AdvancedWeb
Server » permet de lancer notre module ESP comme serveur en le connectant à un réseau (passé en paramètre dans notre code). J’ai opté pour cet exemple car il permet également d’insérer facilement un code HMTL qui sera à la racine de notre serveur. Ainsi, après avoir chargé notre site sur le module et l’avoir branché, nous sommes capables d’afficher notre site sur un navigateur (sur une machine connectée au même réseau que l’ESP32). De plus, puisque le code HTML s’actualise toutes les secondes sur le module, le site est très régulièrement mis à jour (cela permettra ainsi de mettre à jour les valeurs de nos mesures sur notre site). 

Dans un second temps, je me suis intéressé à la librairie SoftwareSerial permettant de faire le raccord entre 2 cartes Arduino (ici entre l’Arduino et l’ESP32). Notre but étant d’envoyer une liste d’informations de l’arduino vers l’ESP, j’ai arrangé le code gérant les capteurs afin que chaque mesure soit stockée dans une liste de chaine de caractères, et ne soit plus simplement affichée sur le moniteur. Ainsi, j’ai dû écrire une fonction « SendData() » envoyant ladite liste de mesures. Par souci de fluidité, j’ai également écrit une fonction « waiting() », qui bloque l’envoie de nouvelles mesures tant que l’ESP32 n’envoie pas de réponse à l’Arduino (validant la réception des mesures précédentes). Du coté de l’ESP32, la fonction « readData() » permet de « découper » les informations reçues, puis de les insérer dans le code HMTL à la racine du serveur ESP. 

Voici ce qui résulte de ce travail :
![site_beta](https://user-images.githubusercontent.com/95374519/151860600-a35ab465-8166-48f8-96f6-fcd4f00407a8.png)
 
N’ayant pas tous les modules à disposition, j’ai arbitrairement mis des valeurs pour la pression et l’anémomètre. Ainsi, la température et l’humidité sont régulièrement mis à jour.
On remarque des soucis d’affichage pour les chaines de caractères, ce qui constituera notre objectif pour les prochaines séances. 

## Séance du 31/01 : 
Au cours de cette séance, l’objectif était de faire fonctionner l’ensemble des modules et d’observer le résultat sur le site hébergé par l’ESP32. 
Après avoir effectué tous les branchements, on constate sur le moniteur série qu’aucune donnée n’est transmise et le code de l’Arduino ne s’exécute pas. En débranchant certains modules et à l’aide d’affichages Serial.print(), on remarque que le capteur de pression BMP180 bloque l’exécution du code de l’Arduino lors de l’appel à la fonction « pressure.begin() » (initialisation de l’objet permettant de récolter la pression). Ne sachant pas s’il s’agissait d’un problème matériel ou non, j’ai isolé la carte Arduino et le capteur BMP180, puis j’ai téléversé le code nécessaire au fonctionnement du capteur seul. Le moniteur série indique alors que le capteur relève bel et bien la pression (environ 1000 mb). 
Ainsi, la source de problème résiderait dans les branchements ou dans l’implémentation du code du capteur BMP180 dans le code gérant l’ensemble des capteurs.
Objectif des prochaines séances :
-	Revoir l’implémentation du code du BMP180 
-	Intégrer les nouveaux capteurs (qualité de l’air et capteur de radiation) au code 
-	Corriger l’affichage des chaines de caractères sur la page HTML.

Voici une photo du montage simple du capteur BMP180, fonctionnant avec l’Atmel tout comme avec l’Arduino :
 

![BMP180_succes1](https://user-images.githubusercontent.com/95374519/151860928-8824cde2-2621-49f9-99ef-07d974fe1ff1.png)

## Séance du 07/02 :
Lors de cette séance, notre objectif a été d’implémenter les deux capteurs (PM2.5 Sensor et Pocket Geiger Type 5+), préparés par Samuel, à l’Arduino gérant l’ensemble des capteurs. 
Dans un premier temps, il m’a fallu arranger le code de chaque capteur afin qu’on puisse envoyer les données mesurées vers l’ESP32. Cela consistait à changer les procédures affichant directement les mesures par des fonctions renvoyant une chaine de caractères.

Par la suite, nous avons dû modifier la librairie utilisée par le capteur Pocket G (« RadiationWatch.h ») puisque celui-ci utilisait des pins déjà attribués à l’anémomètre et à la girouette (I/O 2 et 3). Cela s’est fait assez aisément en se référant à la documentation accompagnant ce capteur (https://github.com/MonsieurV/ArduinoPocketGeiger.git). Cependant, lors des premiers essaies d’envoie de données vers l’ESP32, l’Arduino ne transmettait aucune information. Il s’agissait d’un défaut de câble qui empêchait l’alimentation des capteurs et donc de l’exécution du code. 

Finalement, le pont entre l’ESP32 et l’Arduino s’est établit et les données se sont correctement envoyées. On remarque cependant que l’Arduino effectue l’envoie de notre liste de données seulement deux fois et se bloque ensuite. Il s’agit très probablement d’une mauvaise gestion de la réception des données du côté de l’ESP32, ce qui reste un problème traitable. Encore faut-il qu’on trouve une solution pour l’affichage des chaines de caractères pour le site. 

### Objectifs des prochaines séances : 
-	Gérer l’affichage des données sur la page HTML
-	Faire en sorte que l’Arduino envoie les mesures en continu
-	Vérifier le bon fonctionnement de l’ensemble des capteurs avec l’Arduino et l’ESP32. 
 
## Séance du 21/02:
Au cours de cette séance, Samuel et moi avons mis en commun le travail effectué durant la pause pédagogique. Lui m’a montré le design de la boite et je lui ai partagé les corrections que j’ai apporté au code.

Nous avions quelques problèmes à gérer à la fin de la dernière séance.

Pour régler le problème d’envoi de données (qui ne se faisait que deux fois), j’ai modifié la façon dont les données été envoyées vers l’ESP32. En effet, dans notre ancien modèle : on récupère nos mesures, on les envoie vers l’ESP, l’arduino attend une réponse de la part de l’esp pour effectuer à nouveau les mesures, l’esp récupère ces données et les classes dans un tableau, puis envoie une réponse à l’arduino et attend pour la lecture de nouvelles données. Le fait que l’esp32 envoyait une réponse à l’arduino perturbait la fonction waiting() de l’esp32 (qui attendait que des données soient disponibles dans le buffer…) qui interprétait la réponse de l’ESP32 comme de nouvelles données de l’arduino. Il en résultait que l’arduino attendait perpétuellement une réponse de l’ESP32 (qui était lu par l’esp et non l’arduino). J’ai ainsi supprimé waiting() du côté de l’arduino qui envoie à présent les données en continu sans attente de réponse de l’esp. 

Quant à l’affichage des données sur la page HTML, j’ai compris après quelques tests que le site ne pouvait afficher une variable de plus de 9 caractères. Pour y remédier il a tout simplement fallu réduire la longueur des chaines de caractères envoyées. 

En mettant tous les capteurs ensemble on a remarqué quelques failles : 
-	Pour le PMSensor, l’une des fonctions nécessaire au prélèvement de mesures fait apparaitre un compteur (il s’agit de « sum » dans readPMSdata() ) qui permet de compter le nombre de bits reçus par le PMSensor. Celui-ci est comparé à un autre compteur (« checksum » qui est le nombre de bits envoyé) qui est modifié dans le PMSensor et non à chaque appel du code dans l’arduino. En raison du délai d’une seconde dans notre loop(), ces deux compteurs se désynchronisaient, ce qui empêchait la lecture des mesures du PMSensor. 
Ainsi, il a fallu réduire le délai dans le loop() et ajouter du code dans readPMSdata() pour permettre la lecture de mesures en continu. 

-	Lors du téléversement de notre croquis sur l’arduinoUNO, on remarque que 85% de la mémoire dynamique (2ko) est occupé par nos variables globales, ce qui empêche la bonne exécution du code. Mr Masson nous a donc préparé une ArduinoMega2600 qui possède bien plus de mémoire dynamique (8ko). J’ai donc supprimé tous les objets SoftwareSerial de notre code puisque l’arduinoMega possède par défaut 3 ports RX/TX.

-	Pour optimiser la gestion de la mémoire dynamique, j’ai réduit le nombre de variables globales. De plus, j’ai appris que l’utilisation de « String » dans le code ajouté toutes les bibliothèques liées à l’objet « String », ce qui occupe davantage de mémoire et d’espace. On m’a suggéré d’utiliser « char* » au lieu. Par ailleurs, afin de supprimer totalement l’utilisation de « String » dans le code, il m’a fallu changer ce qui nous permettait de stocker les mesures : un tableau de « string », ce qui me forçait à convertir toutes les mesures en « string »… Pour résoudre ce problème, j’ai remplacé le tableau de mesures par une structure, ce qui permet d’accueillir des valeurs hétérogènes. 
Finalement, j’ai reformulé la collecte des mesures et l’envoi des données vers l’ESP32 (en écrivant « sendAlldata() » et « collectData() »).
Il sera peut-être possible que l’on s’affranchisse de l’arduinoMega et que l’on poursuive notre travail sur l’arduinoUno, puisque la mémoire dynamique occupée s’est vu réduite. 

-	Dans l’implémentation du PocketG, nous avons du mal à récupérer les données mesurées par le capteur. En effet, l’affichage des données sur le moniteur se fait grâce à une fonction (radiation.loop() ) définie dans la bibliothèque accompagnant le capteur. Ainsi, il nous faut encore étudier en profondeur cette bibliothèque et dégager la fonction renvoyant les mesures. 
Il nous reste encore à trouver un moyen de rendre notre projet indépendant de nos ordinateurs (recourt aux batteries) et d’agencer tous nos capteurs dans le réceptacle que nous sommes en train de produire. 

Données envoyées par l’arduino :
![moniteur](https://user-images.githubusercontent.com/95374519/155217702-6c2d5232-c516-49aa-80dc-619c80cfa776.png)

Montage sans le PocketG et l’anémomètre :
![montage](https://user-images.githubusercontent.com/95374519/155217677-ad5647e8-a255-4fbd-bea1-27d5aa18ad52.jpg)

Résultat sur la page web :
![Site_gamma](https://user-images.githubusercontent.com/95374519/155217646-64b1050a-0281-4170-9a1f-14d72320d68d.png)
