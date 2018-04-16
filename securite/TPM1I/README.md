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
                Modulus:
                    00:bd:ad:b4:bc:a5:01:9c:26:48:c2:58:6e:b8:c8:
                    55:7b:55:ca:ba:c8:eb:4f:e2:46:d9:2b:10:62:56:
                    99:ca:46:b5:d3:f0:9f:9c:e5:26:ba:fe:30:88:34:
                    49:a2:10:b7:03:c9:7e:f6:fd:54:15:31:53:b3:d5:
                    3f:1e:f0:8b:e5:71:0c:4c:82:b4:1a:c9:93:43:08:
                    1e:d5:bf:9a:ac:86:5b:b6:14:92:d5:8d:c4:08:e7:
                    bc:a3:ed:fa:17:76:41:5a:a8:e9:f4:15:15:d1:69:
                    38:9e:f6:03:8a:07:96:0b:ae:b8:f5:f8:a5:b5:7f:
                    47:e9:f7:2a:80:ca:32:d8:69
                Exponent: 65537 (0x10001)
        Attributes:
            a0:00
    Signature Algorithm: sha256WithRSAEncryption
         7d:b3:06:e0:7a:b6:bb:53:93:20:09:2b:8c:3a:08:7d:28:93:
         7d:e8:23:48:fc:d6:44:02:85:41:09:08:12:df:f7:f3:99:55:
         2a:a9:4b:c9:2c:f0:0d:8b:88:6f:0e:82:2d:a1:7f:62:f4:40:
         ca:1b:32:c1:16:f4:26:3e:be:6e:db:ec:53:7c:e7:91:31:0e:
         3d:fb:80:03:63:89:d1:3d:6d:df:4b:65:01:21:d4:32:34:68:
         7d:3c:b6:12:c3:b0:ca:cc:c2:52:8a:a8:24:bd:30:0c:d7:b1:
         0d:4f:5f:44:7d:98:4c:50:21:de:8d:90:2e:17:79:cb:6d:14:
         03:bd
```

La clé privée n'y figure pas, il y a cependant le module, l'exposant, l'algorithme de cryptage, l'algorithme de signature.
