# 🐣 S1 | Prog: Workshop (Solution)

- [📅 Planning](#-planning)
  - [Lundi](#lundi)
    - [Prof 9h30-12h45 (pause 11h00-11h15)](#prof-9h30-12h45-pause-11h00-11h15)
    - [Élève](#élève)
  - [Mardi](#mardi)
    - [Matin 9h30-12h45 (pause 11h00-11h15)](#matin-9h30-12h45-pause-11h00-11h15)
      - [Prof](#prof)
      - [Élève](#élève-1)
    - [Aprèm](#aprèm)
      - [Prof 13h45-17h (pause 15h15-15h30)](#prof-13h45-17h-pause-15h15-15h30)
      - [Élève](#élève-2)
  - [Mercredi](#mercredi)
    - [Prof 9h30-10h30](#prof-9h30-10h30)
    - [Élève](#élève-3)
  - [Jeudi](#jeudi)
    - [Prof 9h30-10h30](#prof-9h30-10h30-1)
    - [Élève](#élève-4)
  - [Vendredi](#vendredi)
    - [Matin 9h30-10h30](#matin-9h30-10h30)
      - [Prof](#prof-1)
      - [Élève](#élève-5)
    - [Aprèm 13h45-17h (pause 15h15-15h30)](#aprèm-13h45-17h-pause-15h15-15h30)
- [📝 Sujet](#-sujet)
  - [Exercices à faire](#exercices-à-faire)
  - [Rapport](#rapport)
  - [Soutenance](#soutenance)
  - [Détails techniques](#détails-techniques)
- [💻 Exercices](#-exercices)
  - [⭐ Ne garder que le vert](#-ne-garder-que-le-vert)
  - [⭐ Noir \& Blanc](#-noir--blanc)
  - [⭐ Channels swap](#-channels-swap)
  - [⭐ Négatif](#-négatif)
  - [⭐⭐ Miroir](#-miroir)
  - [⭐⭐ Rotation de 90°](#-rotation-de-90)
  - [⭐⭐ Color glitch](#-color-glitch)
  - [⭐⭐ Luminosité](#-luminosité)
  - [⭐⭐⭐ Position glitch](#-position-glitch)
  - [⭐⭐⭐ Vortex](#-vortex)
  - [⭐⭐ RGB split](#-rgb-split)
  - [⭐ Dessiner un dégradé](#-dessiner-un-dégradé)
  - [⭐⭐ Dessiner un disque](#-dessiner-un-disque)
    - [⭐ Dessiner un cercle](#-dessiner-un-cercle)
    - [⭐⭐⭐ Dessiner une rosace](#-dessiner-une-rosace)
  - [⭐⭐⭐ Dessiner la fractale de Mandelbrot](#-dessiner-la-fractale-de-mandelbrot)
  - [⭐⭐⭐⭐⭐ K-means : trouver les couleurs les plus présentes dans une image](#-k-means--trouver-les-couleurs-les-plus-présentes-dans-une-image)
  - [⭐⭐⭐⭐ Convolutions](#-convolutions)
    - [⭐ Netteté, Contours, etc.](#-netteté-contours-etc)
    - [⭐⭐ Filtres séparables](#-filtres-séparables)
    - [⭐⭐ Difference of gaussians](#-difference-of-gaussians)
  - [⭐⭐⭐(⭐) Histogram Equalization](#-histogram-equalization)
  - [Feel free to implement your own effects!](#feel-free-to-implement-your-own-effects)
  - [⭐⭐⭐⭐⭐ Filtre de Kuwahara (effet peinture à l'huile)](#-filtre-de-kuwahara-effet-peinture-à-lhuile)
  - [⭐⭐⭐ Tramage](#-tramage)
  - [⭐⭐⭐⭐ Pixel sorting](#-pixel-sorting)
  - [⭐⭐⭐⭐⭐⭐ Diamond Square](#-diamond-square)
    - [⭐⭐ Colorer la height map](#-colorer-la-height-map)
  - [⭐⭐ Mosaic](#-mosaic)
    - [⭐⭐⭐ Mosaic flip](#-mosaic-flip)


## 📅 Planning

### Lundi

#### Prof 9h30-12h45 (pause 11h00-11h15)

- [ ] Présentation de moi
- [ ] Présentation du projet
  - [ ] C'est quoi le sujet? -> faire des effets sur les images, comme on peut en trouver dans photoshop etc, filtre insta etc
  - [ ] Par groupe de 2, et 1 groupe de 3 si impair. Mais je veux que vous fassiez chacun des exercices de votre côté autant que possible, et que vous vous entraidiez au besoin. + pour l'exercice 3+ faites le à deux
  - [ ] Evaluation: min 1 exo de niveau 3 ou +, et autant du reste que possible. Montrez moi juste que vous êtes investies, 4h d'autonomie par jour c'est très bien. Posez un max de question, quand vous êtes bloquées et/ou par curiosité.
  - [ ] Je vous encourage à dans un premier temps essayer de faire chaque exercice sans regarder les indices, ni chercher sur internet / ChatGPT. Essayez de résoudre le problème par vous-même, ça aide à mieux le comprendre, puis apprécier et retenir la solution. + si vous réussissez seul.e, giga satisfaction. Les exos sont "faciles", c'est fait pour. Bien sûr que ChatGPT peut les résoudre, mais vous n'apprendrez rien si vous n'essayez pas par vous même. Et plutôt que ChatGPT, demandez moi en premier si possible, je pourrai mieux vous aiguiller / expliquez juste comme il faut pour que vous appreniez un max. Ou sinon demandez à vos camarades en deuxième solution (+ c'est un bon exercice d'expliquer donc vous rendez service à la fois à vous-même et à elleux)   
- [ ] Présentation de la lib
  - [ ] Parler de la représentation des couleurs en vec3 avec des valeurs de 0 à 1
  - [ ] Mentionner que pour faire les choses bien il ne faudrait pas travailler en sRGB mais dans un espace perceptuellement correct (CIELab, Oklab)
  - [ ] Mentionner que la lib n'est pas un exemple de la meilleure API de l'univers, elle est minimaliste pour les forcer à écrire un max de code, se rendre compte des problèmes qui peuvent survenir, pas trop leur mâcher le travail. (Par exemple, on devrait permettre de gérer un wrap mode, et faire les conversions d'espace de couleur automatiquement, et pouvoir itérer sur les lignes ou sur les colonnes, et aussi le fait que le chemins soient relatifs au dossier contenant le CMakeLists.txt c'est atroce en production)

#### Élève

- [ ] Création du groupe : binôme obligatoirement (et 1 trinôme dans la classe si impair) mais je veux que vous fassiez chacun des exercices de votre côté autant que possible, et que vous vous entraidiez au besoin. + pour l'exercice 3+ faites le à deux
- [ ] Prise en main de la lib
- [ ] Quelques exercices de niveau 1 (⭐) et/ou 2 (⭐⭐)

### Mardi

#### Matin 9h30-12h45 (pause 11h00-11h15)

##### Prof

- [ ] Présentation de git

##### Élève

- [ ] Création du git
- [ ] Test et prise en main de git (l'un push quelque chose et l'autre le pull par exemple)
- [ ] Mettre sur le repository les exercices que vous avez fait hier

#### Aprèm

##### Prof 13h45-17h (pause 15h15-15h30)

- [ ] Présentation des algos avancés (niveau 3 ou plus ⭐⭐⭐)
- [ ] Conseil : faites un fichier à part pour votre algo avancé, car il y aura probablement plusieurs fonctions intermédiaires à écrire, et peut-être des structs aussi.

##### Élève

- [ ] Choix de l'algo que vous allez implémenter (niveau 3 ou plus ⭐⭐⭐)
- [ ] Commencer à vous renseigner sur votre algo avancé, à l'implémenter

### Mercredi

#### Prof 9h30-10h30

- [ ] Si besoin, point de rappel sur une notion mal acquise.
- [ ] Passer voir les groupes, regarder l'algo avancé qu'iels ont choisi.


#### Élève

- [ ] Avancer sur l'algo avancé

### Jeudi

#### Prof 9h30-10h30

- [ ] Si besoin, point de rappel sur une notion mal acquise.
- [ ] Passer voir les groupes et décider qui présente quel algo. Possibilité que plusieurs groupes se mettent ensemble pour présenter leur algo si tout le monde a envie de passer.

#### Élève

- [ ] Finir votre algo avancé


### Vendredi

#### Matin 9h30-10h30

##### Prof

- [ ] Présentation de Markdown pour l'écriture du rapport
  - [ ] Extension VSCode, et comment elle permet de générer une Table of Content
  - [ ] Syntaxe basique (titres, gras, italique, blocs de code, bloc quote, liste), et si voulez vous pouvez aller voir comment [le document que vous êtes en train de lire](TODO mettre le lien du sujet qui est sur le git) est écrit, c'est du markdown !
  - [ ] [Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)
  - [ ] Mettre des images (s'assurer du coup que leur dossier output soit à la racine du repo, et soit commit)
  - [ ] Vous pouvez mettre du html si vous voulez faire des trucs + avancés.

##### Élève

- [ ] Écriture du rapport. (Vous avez jusqu'à lundi matin pour les rendre).
- [ ] Préparation de la présentation pour celleux concerné.es

#### Aprèm 13h45-17h (pause 15h15-15h30)

- [ ] Présentations


## 📝 Sujet

### Exercices à faire

Faites un maximum de chose, et au minimum un exercice de niveau 3 ou plus (⭐⭐⭐). Vous êtes aussi les bienvenu.es pour inventer vos propres effets !

### Rapport

A faire en Markdown obligatoirement (si vous ne connaissez pas c'est l'occasion de découvrir, c'est super utile).

A mettre directement en tant que readme à la racine du repo.

Faite une section par exercice que vous avez fait. Montrez une image avant et après application de l'effet (comme c'est fait dans l'énoncé des exercices). Si vous jugez cela utile, vous pouvez mettre un petit texte expliquant des spécificités de l'algo que vous avez implémenté. (C'est surtout intéressant si vous avez fait des algos qui ne sont pas listés dans le sujet, et pour votre algo 3+).

Mettez un lien vers votre git au début du rapport.

### Soutenance

Présentez un des algos avancés que vous avez fait, en 5 minutes. C'est de la vulgarisation, il faut que tous vos camarades puissent comprendre, au moins dans les grandes lignes.

> Est-ce que c'est utile ? Ca prend pas mal de temps. Mais de l'autre côté c'est un bon exercice qui force à avoir bien compris l'algo, et ça permet aux autres de voir les algos qu'iels n'ont pas implémenté. Ou sinon, je demande juste aux groupes les plus chauds de faire une présentation, comme ça c'est pas trop long, et on voit juste une fois chaque algo. Et on peut prendre + de temps pour chaque présentation (même pas besoin de limiter le temps, iels font comme bon leur semble).

### Détails techniques

Nous utiliserons la librairie *sil* pour lire, éditer et re-sauvegarder les images. Elle est très simple à utiliser et n'expose que le minimum nécessaire. Vous pouvez trouver sa documentation [sur GitHub](https://github.com/JulesFouchy/Simple-Image-Lib/tree/main#usage).

## 💻 Exercices

- Leur dire de travailler sur une image pas trop grande, pour que le rendu soit quasi-instantané. (Par exemple l'image par défaut fournie dans le projet est très bien. Mais il faut leur fournir aussi une photo, certains effets ne marchent pas bien sur une image en flat design).
- Leur dire d'afficher l'image output à côté dans VSCode pour facilement voir le résultat
![Alt text](image.png)

### ⭐ Ne garder que le vert

![](output/keep_green_only.png)

<details><summary>Indice</summary>
Mettre le rouge et le bleu à 0.
</details>

### ⭐ Noir & Blanc

![](output/black_and_white.png)

N'hésitez pas à **aller chercher la formule sur internet** si besoin !

### ⭐ Channels swap

![](output/channels_swap.png)

Par exemple, échangez le canal rouge et le canal bleu.

### ⭐ Négatif

![](output/negative.png)

### ⭐⭐ Miroir

![](output/mirror.png)

Symétrie par rapport à l'axe Y (vertical).

### ⭐⭐ Rotation de 90°

![](output/rotate_90_degrees.png)

La formule générique pour un angle quelconque est un peu plus compliquée, mais pour 90° il y a une formule vraiment simple, essayez de la trouver !

### ⭐⭐ Color glitch

![](output/color_glitch.png)

Remplacer quelques pixels au hasard par une couleur aléatoire.

Pour obtenir des nombres aléatoires, includez le fichier `"random.hpp"` et utilisez soit `random_int(min, max)` soit `random_float(min, max)`. Si vous voulez que votre programme utilise les mêmes nombres aléatoires à chaque fois que vous l'utilisez, vous pouvez définir une seed avec `set_random_seed(0)` au début de votre `main()` (vous pouvez passer n'importe quel nombre autre que 0, ça définira quels seront les nombres générés par les fonctions random).

### ⭐⭐ Luminosité

| ![](images/photo.jpg)  | ![](output/luminosity+.jpg)  |![](output/luminosity-.jpg)  |
|---|----|----|
| Image originale | Après éclaircissement | Après assombrissement |

<details><summary>Indice</summary>
On voudrait des courbes comme celles-ci, qui diminuent tous les nombres entre 0 et 1 (courbe bleue) (c-à-d assombrisse), ou les augmentent (courbe verte) (c-à-d éclaircisse), tout en gardant 0 à 0 et 1 à 1 (afin de garder la plage dynamique de l'image, pour conserver des noirs purs et des blancs purs).
<img src ="image-1.png"/>
</details>
<details><summary>Indice 2</summary>
Les fonctions puissance font exactement ce qu'on veut!<br/>
La preuve: <a src="https://www.desmos.com/calculator/c3ztk51mng">https://www.desmos.com/calculator/c3ztk51mng</a>
</details>

### ⭐⭐⭐ Position glitch

![](output/position_glitch.png)

Pour obtenir des nombres aléatoires, includez le fichier `"random.hpp"` et utilisez soit `random_int(min, max)` soit `random_float(min, max)`. Si vous voulez que votre programme utilise les mêmes nombres aléatoires à chaque fois que vous l'utilisez, vous pouvez définir une seed avec `set_random_seed(0)` au début de votre `main()` (vous pouvez passer n'importe quel nombre autre que 0, ça définira quels seront les nombres générés par les fonctions random).

<details><summary>Indice</summary>
Prendre un rectangle de pixels et l'intervertir avec un autre rectangle de pixels, ailleurs dans l'image. Faire ça plusieurs fois.
</details>

### ⭐⭐⭐ Vortex

![](output/vortex.png)

<details><summary>Indice</summary>
Chaque pixel subit une rotation, de plus en plus importante au fur et à mesure qu'on s'éloigne du centre.
</details>

### ⭐⭐ RGB split

![](output/rgb_split.png)

⚠️ Créez une nouvelle image et travaillez sur celle-ci. Il ne faut pas modifier l'image originale pendant que vous bouclez pour appliquer l'effet, sinon certains pixels n'utiliseront pas la bonne couleur de l'image originale, mais plutôt la couleur déjà modifiée par un pixel précédent, ce qui pourrait vous donner ce genre de rendu moins intéressant :

![](output/rgb_split_incorrect.png)

### ⭐ Dessiner un dégradé

![](output/gradient.png)

Vous pouvez créer une image noire avec
```cpp
sil::Image image{300/*width*/, 200/*height*/};
```
puis itérer sur les pixels pour les colorer.

### ⭐⭐ Dessiner un disque

![](output/disk.png)

Vous pouvez créer une image noire avec
```cpp
sil::Image image{500/*width*/, 500/*height*/};
```

<details><summary>Indice</summary>
Ensuite, à vous de parcourir les pixels et de les colorier ou non en fonction de si ils sont à l'intérieur du disque. La fonction prendra en paramètre le centre et le rayon du disque.
</details>

#### ⭐ Dessiner un cercle

![](output/circle.png)

En reprenant et modifiant légèrement votre code pour le disque, écrivez le code qui donne un cercle. (Son contour aura une épaisseur donnée `thickness`).

#### ⭐⭐⭐ Dessiner une rosace

![](output/rosace.png)

Maintenant que vous savez dessiner un cercle, dessinez-en plusieurs sur la même image, à des positions bien choisies, de sorte à dessiner une rosace.
(PS: il va surement falloir faire de la trigo!)

### ⭐⭐⭐ Dessiner la fractale de Mandelbrot

![](output/mandelbrot.png)

<details><summary>Indice</summary>
Définir un nombre max d'itérations, itérer `z <- z * z + c` jusqu'à ce qu'on dépasse ce nombre d'itérations ou que la norme de z soit > 2, puis assigner une couleur en fonction du nombre d'itérations qu'on a fait avant de sortir de la boucle.
</details>

### ⭐⭐⭐⭐⭐ K-means : trouver les couleurs les plus présentes dans une image

| ![](images/photo.jpg)  | ![](output/k_means_2_colors.jpg) | ![](output/k_means_3_colors.jpg)  | ![](output/k_means_16_colors.jpg)  |
|---|----|----|----|
| Originale | 2 couleurs | 3 couleurs | 16 couleurs |

Trouvez les k couleurs les plus représentatives de l'image, puis assignez à chaque pixel la couleur dont il est le plus proche parmi les k.

Voici une bonne vidéo expliquant l'algorithme :

[![k-means video](https://img.youtube.com/vi/yR7k19YBqiw/0.jpg)](https://www.youtube.com/watch?v=yR7k19YBqiw)

Pour obtenir des nombres aléatoires, includez le fichier `"random.hpp"` et utilisez soit `random_int(min, max)` soit `random_float(min, max)`. Si vous voulez que votre programme utilise les mêmes nombres aléatoires à chaque fois que vous l'utilisez, vous pouvez définir une seed avec `set_random_seed(0)` au début de votre `main()` (vous pouvez passer n'importe quel nombre autre que 0, ça définira quels seront les nombres générés par les fonctions random).

### ⭐⭐⭐⭐ Convolutions

![](output/box_blur.png)
*Box blur*

Les convolutions permettent d'implémenter plein d'effets (flou, détection de contour, augmentation de la netteté, etc.). L'effet va varier en fonction du *kernel* que vous utilisez lors de votre convolution. Tout est expliqué dans cette excellente vidéo, entre 1m10 et 4m18:

[![convolution video](https://img.youtube.com/vi/8rrHTtUzyZA/0.jpg)](https://www.youtube.com/watch?v=8rrHTtUzyZA)

Conseil: une fois que vous savez que votre algo marche, si vous voulez tester avec des kernels plus gros, ça peut être lent, donc vous avez intérêt à build en release et lancer sans debugger attaché (demandez-moi si vous ne savez pas comment faire).

#### ⭐ Netteté, Contours, etc.

| ![](output/emboss.png)  | ![](output/outline.png)  |![](output/sharpen.png)  |
|---|----|----|
| Emboss | Outline | Sharpen |

Sur [ce site](https://setosa.io/ev/image-kernels/) vous pourrez trouver différents kernels pour faire différents effets.

#### ⭐⭐ Filtres séparables

| Box blur naïf, 100x100  | Box blur séparé, 100x100 |
|---|----|
| ![](output/big_box_blur.png) | ![](output/big_box_blur_separable_filter.png) |
| 7.44 secondes | 0.18 secondes |

Quand vous voulez faire un gros flou il faut augmenter la taille du kernel, ce qui peut considérablement ralentir l'algorithme. Heureusement, certains kernels ont une propriété qui nous permet de calculer leur convolution **BEAUCOUP** plus rapidement. Le *box blur* et le *gaussian blur* sont de tels kernels. Voici une vidéo expliquant tout ça:

[![separable filters video](https://img.youtube.com/vi/SiJpkucGa1o/0.jpg)](https://www.youtube.com/watch?v=SiJpkucGa1o)

#### ⭐⭐ Difference of gaussians

![](output/difference_of_gaussians.png)

https://youtu.be/5EuYKEvugLU

Ne faire que le début ça suffit, jusqu'à 4m09.

### ⭐⭐⭐(⭐) Histogram Equalization

| ![](images/photo_faible_contraste.jpg)  | ![](output/normalize_histogram.jpg)  |
|---|----|
| Avant | Après |

Amélioration du contraste, en calculant la luminosité min et max, et en appliquant une transformation qui va mapper le plus sombre à 0 et le plus clair à 1.
(PS: testez avec l'image "images/photo_faible_contraste.jpg", vous verrez bien l'intérêt de l'effet.)

### Feel free to implement your own effects!

### ⭐⭐⭐⭐⭐ Filtre de Kuwahara (effet peinture à l'huile)

![](output/kuwahara.jpg)

https://youtu.be/LDhN-JK3U9g

(Juste la version simple, qui est expliquée entre 3:11 et 3:30, suffit. Si vous voulez aller plus loin, vous êtes les bienvenu.es bien sûr 😉)

### ⭐⭐⭐ Tramage

![](output/ordered_dithering.png)

Vous pouvez lire [ce super article](https://surma.dev/things/ditherpunk/) sur le tramage (a.k.a. *dithering* en anglais).

Sur l'image ci-dessus j'ai utilisé de l'*ordered dithering* avec une matrice de Bayer 4x4 (a.k.a. de niveau 1). Tout est expliqué dans l'article ci-dessus ! (Plus précisément, j'ai repris la matrice et le code depuis [cet autre article](https://medium.com/the-bkpt/dithered-shading-tutorial-29f57d06ac39).)

### ⭐⭐⭐⭐ Pixel sorting

![](output/pixel_sorting.png)

Voici une bonne vidéo expliquant l'algorithme (vous pouvez ignorer le début spécifique à Processing où on voit comment afficher l'image) :

[![pixel sorting video](https://img.youtube.com/vi/JUDYkxU6J0o/0.jpg)](https://www.youtube.com/watch?v=JUDYkxU6J0o)

Ensuite, au lieu de trier tous les pixels de l'image, triez par colonne (ou par ligne), pour un effet plus joli.

Pour trier un tableau, vous pouvez utiliser [`std::sort`](https://www.geeksforgeeks.org/sort-c-stl/).

Plutôt que d'utiliser `pixel(x, y)` vous avez probablement intérêt à utiliser à utiliser `pixels()` pour récupérer le tableau contenant tous les pixels de l'image.

Pour obtenir des nombres aléatoires, includez le fichier `"random.hpp"` et utilisez soit `random_int(min, max)` soit `random_float(min, max)`. Si vous voulez que votre programme utilise les mêmes nombres aléatoires à chaque fois que vous l'utilisez, vous pouvez définir une seed avec `set_random_seed(0)` au début de votre `main()` (vous pouvez passer n'importe quel nombre autre que 0, ça définira quels seront les nombres générés par les fonctions random).

### ⭐⭐⭐⭐⭐⭐ Diamond Square

![](output/diamond_square_greyscale.png)

Algorithme de génération de height map, qui peut ensuite être utilisée pour créer des terrains prrocéduraux dans des jeux vidéos par exemple.

Voici une bonne vidéo expliquant l'algorithme:
[![diamond square video](https://img.youtube.com/vi/4GuAV1PnurU/0.jpg)](https://www.youtube.com/watch?v=4GuAV1PnurU)

Conseil: commencez par travailler sur une image toute petite (e.g. 17x17), afin de bien voir les pixels et ce qu'il se passe.

#### ⭐⭐ Colorer la height map

![](output/diamond_square_colored.png)

<details><summary>Indice</summary>
Avec `glm::mix(color1, color2, pourcentage);` vous pouvez faire un mélange entre deux couleurs données.
</details>
<details><summary>Indice 2</summary>
Essayez par exemple de faire un dégradé de bleu quand le niveau de gris est entre 0 et 0.5, et un dégradé entre du vert et du marron quand le niveau de gris est entre 0.5 et 1.
</details>

### ⭐⭐ Mosaic

![](output/mosaic.png)

<details><summary>Indice</summary>
You can use a modulo (`%`) somewhere.
</details>

#### ⭐⭐⭐ Mosaic flip

Flip every other image:

![](output/mosaic_flip.png)