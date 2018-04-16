# TP Long noté : Open SSL

## Schéma général

1. Déchiffrer fichier F du .zip, {F},,mdp,, avec mdp = md5^(-1) (suite hex)

    - inverser __md5__ via site web
    - déchiffrer {F},,mdp,,

2. Rechiffrer F via __1 clé__ et __IV (Initialisation Vector) = 0__

    - transmettre {F},,k,, avec k transmis dans 1 enveloppe digitale par ma clé publique et {K},,PKBM,,

3. Créer votre certificat utilisant M1I.cert comme CA -> utile pour signer le CR

__/!\ Bien faire les tests entre vous pour que tout marche bien !__

Ne pas chiffrer vos clés ! Me rendre au moins votre certificat {F},,k,, {K}PKMB CR||{CR},,SKEdu,, <= signature

## Notes

- Génération clé RSA : rien mettre
- Génération clé shared : toto

## Exercice 2 : Générateur pseudo-aléatoire

Pour générer un pseudo aléatoire en hex de 16 bytes ( 128 bits ) : `openssl rand -hex 16`

## Exercice 3 : Clés secrètes

### a)

- 4528e6a7bb9341c36c425faf40ef32c3 === __pass__ (md5 decrypted)
- a39cce46f68858d14998c58f03aabdcf === __simple__ (md5 decrypted)

### b)

Le bon mot de passe était __simple__ : `openssl enc -des-ede-cbc -d -in aDechiffrer.crypt -out aDechiffrer.decrypt`

### c)

Le fichier décrypté est un peu plus petit, car lors de l'encryption on crypte par blocs de 32 bits, comme la taille du fichier n'est pas forcément un multiple de 32 bits, on fait du **padding** et on complète avec des 0 jusqu'à la fin.

