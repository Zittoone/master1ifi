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

## Exercice 4 : Clés publiques

### 4.1) Généralisation des clés

#### openssl genrsa -out [fichier] [taille]

1. `openssl genrsa -out courte.pem 32`

2. `openssl genrsa -out Etud.pem 1024`

#### openssl rsa -in [fichier] -text

1. Affichage en clair

    ``` shell
    $ openssl rsa -in courte.pem -text
    Private-Key: (32 bit)
    modulus: 3121741939 (0xba120073)
    publicExponent: 65537 (0x10001)
    privateExponent: 2054349233 (0x7a72e1b1)
    prime1: 61813 (0xf175)
    prime2: 50503 (0xc547)
    exponent1: 27413 (0x6b15)
    exponent2: 28877 (0x70cd)
    coefficient: 17582 (0x44ae)
    writing RSA key
    -----BEGIN RSA PRIVATE KEY-----
    MCsCAQACBQC6EgBzAgMBAAECBHpy4bECAwDxdQIDAMVHAgJrFQICcM0CAkSu
    -----END RSA PRIVATE KEY-----
    ```
    ``` shell
    $ openssl rsa -in Etud.pem -text
    Private-Key: (1024 bit)
    ... Trop grand, refaire la commande ^
    ```

2. L'effet du paramètre __-noout__ n'affiche pas la clé en sortie.

3. L'effet du paramètre __-pubout__ permet d'afficher la partie publique d'une clé.

4. On a `61813 * 50503 = 3121741939`

5. Le module est `3121741939` et on a le produit égal à `3121741939`. C'est donc bon.

6. `openssl rsa -in Etud.pem -pubout > EtudPK.pem`

### 4.2) Chiffrement de données

> `openssl rsautl -encrypt -in <fichier_entree> -inkey <cle> -out <fichier_sortie>`

Test avec clé privée connue :

`$ openssl rsautl -encrypt -in pseudo_aleatoire -inkey EtudPK.pem -pubin -out DigitEnv.rsa`

`$ openssl rsautl -decrypt -in DigitEnv.rsa -inkey Etud.pem -out pseudo_aleatoire.decrypt`

Commandes supposées du prof :

`$ openssl rsautl -encrypt -in pseudo_aleatoire -inkey BMPK.pem -pubin -out DigitEnv.rsa`

`$ openssl rsautl -decrypt -in DigitEnv.rsa -inkey BMK.pem -out pseudo_aleatoire.decrypt`

1. `$ openssl enc -aes-128-cbc -K $(cat pseudo_aleatoire) -iv 0 -in aDechiffrer.decrypt -out reChiffre.crypt`

2. `$ openssl enc -aes-128-cbc -K $(cat pseudo_aleatoire.decrypt) -d -iv 0 -in reChiffre.crypt -out reChiffre.decrypt`

*reChiffre.decrypt* a bien le même contenu que *aDechiffrer.decrypt* !

### 4.3) Signature de données

- Calcul de l'empreinte : `openssl dgst <hachage> -out <empreinte> <fichier_entrée>` (où hachage est une fonction de hachage à choisir parmi -md5 -sha1 ou -ripemd160)

- Signature avec l'empreinte : `openssl rsautl -sign -in <empreinte> -inkey <key> -out <signature>`

- Vérification : `openssl rsautl -verify -in <signature> -inkey <cle> -out <empreinte>`

- Calcul empreinte + signature : `openssl dgst <hachage> -sign <cle> -out <signature> <fichier_entrée>`

- Vérification empreinte produite == empreinte calculée : `openssl dgst <hachage> -verify <cle> -signature <signature> <fichier_entree>`

## 5 Certificats

### 5.1) Création d’une requête de certificats

__Création :__

```shell
$ openssl req -new -key Etud.pem -out maRequete.csr
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [AU]:FR
State or Province Name (full name) [Some-State]:PACA
Locality Name (eg, city) []:Sophia-Antipolis
Organization Name (eg, company) [Internet Widgits Pty Ltd]:UCA
Organizational Unit Name (eg, section) []:Deptinfo
Common Name (e.g. server FQDN or YOUR name) []:
Email Address []:alexiscouvreur.pro@gmail.com

Please enter the following 'extra' attributes
to be sent with your certificate request
A challenge password []:
An optional company name []:
```

__Lecture :__

```shell
$ openssl req -in maRequete.csr -text -noout
Certificate Request:
    Data:
        Version: 1 (0x0)
        Subject: C = FR, ST = PACA, L = Sophia-Antipolis, O = UCA, OU = Deptinfo, emailAddress = alexiscouvreur.pro@gmail.com
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption
                Public-Key: (1024 bit)
                ...
```

La clé privée n'y figure pas, il y a cependant le module, l'exposant, l'algorithme de cryptage, l'algorithme de signature.

### 5.2) Demande de signature de certificat

#### 5.2.1) L’autorité de certification M1I

1. Le certificat est valable jusqu'au __2 Décembre 2018 à 18:46:46 GMT__. Et la clé a une taille de __1024 bits__.
    ```shell
    $ openssl x509 -in M1I.pem -text -noout
    ...
    Validity
        Not Before: Dec  2 18:46:46 2017 GMT
        Not After : Dec  2 18:46:46 2018 GMT
    Subject: C = fr, ST = PACA, L = Sophia Antipolis, O = Univ. Nice Sophia Antipolis, OU = Dpt of Computer Science, CN = ICS_CA, emailAddress = Bruno.Martin@unice.fr
    Subject Public Key Info:
        Public Key Algorithm: rsaEncryption
            Public-Key: (1024 bit)
    ...
    ```

#### 5.2.2) Création du certificat

1. Création du certificat
    ```shell
    $ openssl x509 -days 10 -CA M1I.pem -CAkey M1I.pem -in maRequete.csr -req -out EtudCert.pem
    Signature ok
    subject=C = FR, ST = PACA, L = Sophia-Antipolis, O = UCA, OU = Deptinfo, emailAddress = alexiscouvreur.pro@gmail.com
    Getting CA Private Key
    ```

2. Vérification

```shell
$ openssl x509 -in EtudCert.pem -text -noout
Certificate:
    Data:
        Version: 1 (0x0)
        Serial Number: 3 (0x3)
    Signature Algorithm: sha256WithRSAEncryption
        Issuer: C = fr, ST = PACA, L = Sophia Antipolis, O = Univ. Nice Sophia Antipolis, OU = Dpt of Computer Science, CN = ICS_CA, emailAddress = Bruno.Martin@unice.fr
        Validity
            Not Before: Apr 16 09:17:56 2018 GMT
            Not After : May 16 09:17:56 2018 GMT
        Subject: C = FR, ST = PACA, L = Sophia-Antipolis, O = UCA, OU = Deptinfo, emailAddress = alexiscouvreur.pro@gmail.com
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption
                Public-Key: (1024 bit)
```

#### 5.2.3) Vérification de certificats

Vérification :

    ```shell
    $ openssl verify -CAfile M1I.pem EtudCert.pem
    EtudCert.pem: OK
    ```