<h1 align="center">Welcome to projet-embarque 👋</h1>
<p>
  <img alt="Version" src="https://img.shields.io/badge/version-0.0.1-blue.svg?cacheSeconds=2592000" />
  <a href="https://twitter.com/YannDurand11" target="_blank">
    <img alt="Twitter: YannDurand11" src="https://img.shields.io/twitter/follow/YannDurand11.svg?style=social" />
  </a>
</p>

> Projet d'un système embarqué pour la dernière année à l'EPSI. Utilisation d'un arduino pour auto-alimenter une plante.

## Objectif

L'objectif du projet était de permettre à une plante de s'auto-alimenter, à l'aide d'arduino, à travers ces aspects :
* Une serveillance du taux d'humidité dans le terreau à travers un capteur dedans
* Une surveillance du niveau d'eau dans la réserve à l'aide d'un capteur
* Une pompe à eau liant la reserve et le terreau, s'activant SI le taux d'humidité relevée est inférieure à l'humidité paramètrer et si la réserve d'eau est suffisante afin de ne pas activer la pompe dans le vide, ce qui l'aurait abîmé
* Un écran indiquant le temps d'humidité actuel
* Un menu, naviguable à travers l'écran et les boutons, afin de paramètrer le taux d'humidité voulu

### Optionnel

* Une lampe afin d'illuminer la plante comme il le faut
* Un menu supplémentaire afin d'afficher et de paramètrer la luminosité

## Schéma

Premier schéma conceptuel du projet
[!schema][/Screenshots/schema-conceptuel.png]

Modèles 3D du projet
[!schema][/Screenshots/pot-assemble.png]

[!schema][/Screenshots/pot-disemble.png]

NB: Le pot le plus gros devait recevoir le système arduino, le second est la reserve d'eau et enfin le plus petit la plante. Dans le temps imparti et les moyens que nous avions ne nous ont pas permis d'avoir 3 pots, nous avons donc du contenir l'eau au plus bas, bloquer avec un fond au milieu afin de séparer l'eau de l'électronique

## Code

### Déclarations des variables

* Capteur d'humidité dans le sol : A5
* Capteur de niveau d'eau : A3
* La pompe à eau : Pin 3
* L'écran LCD et les 6 boutons : Shield Arduino utilisant les pins :
  * lcd : 8, 9, 4, 5, 6, 7
  * Boutons : Pins définit par le shield
* Utilisation des librairy Wire et LiquidCrystal

## Author

👤 **Yann Durand**

* Website: https://codewithnefaden.wordpress.com
* Twitter: [@YannDurand11](https://twitter.com/YannDurand11)
* Github: [@Nefaden](https://github.com/Nefaden)

👤 **Hugo Herault**

👤 **Helori Gouin**

👤 **Marouwane Bah**

👤 **Emmanuel Chauveau**

## Show your support

Give a ⭐️ if this project helped you!

***
_This README was generated with ❤️ by [readme-md-generator](https://github.com/kefranabg/readme-md-generator)_
