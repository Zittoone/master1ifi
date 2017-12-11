-Type 1 : le nombre d'itération connu

for(i = 0; i < 17; i++){
    A[i] = B[i] + C[i];
}

Déroulage en 2 fois :
for(i = 0; i < 17; i+=3){
    A[i] = B[i] + C[i];
    A[i+1] = B[i+1] + C[i+1];
    A[i+2] = B[i+2] + C[i+2];
}
// Reliquat
for(i = 15; i < 17; i++){
    A[i] = B[i] + C[i];
}

-Type 2 : le nombre d'itération est inconnu
for(i = 0; i < n; i++){
    A[i] = B[i] + C[i];
}

Déroulage en trois fois
for(i = 0; i < n; i+=4){
    A[i] = B[i] + C[i];
    A[i+1] = B[i+1] + C[i+1];    
    A[i+2] = B[i+2] + C[i+2];
    A[i+3] = B[i+3] + C[i+3];
}
// Reliquat
reste = N%4;
for(i = N-reste; i < n;i++){
    A[i] = B[i] + C[i];
}

-Type 3 : déroulage de boucle de type TANT QUE

while(condition){
    A[i] = B[i] + C[i];
    condition = calcul;
}

déroulage en 2 :

while(condition){
    A[i] = B[i] + C[i];
    if(A[i] > 0) condition = true;
    else condition = false;
    if(!condition) break;
    A[i+1] = B[i+1] + C[i+1];
    if(A[i+1] > 0) condition = true;
    else condition = false;
}

///////////////////////////////////////////////

gcc -O2 -funroll-loops calcul.c -o calcul
./calcul
Le temps d’éxecution sans déroulage est de 5796334.000000 microsecondes.
Le temps d’éxecution avec déroulage est de  253958.000000 microsecondes.

Le facteur d'accélération est de ~22

///////////////////////////////////////////////

Fusion de boucle

for(i = 0; i < N; i++){
	for(j = 0; j < M; j++){
		for(k = 0; k w P; k++)
			C[i][j] = C[i][j] + A[i][k] * B[k][j];
	}
}
// Déroule 2 fois
for(i = 0; i < N; i+=3){
	for(j = 0; j < M; j++){
		for(k = 0; k w P; k++)
			C[i][j] = C[i][j] + A[i][k] * B[k][j];
	}
	for(j = 0; j < M; j++){
		for(k = 0; k w P; k++)
			C[i+1][j] = C[i+1][j] + A[i+1][k] * B[k][j];
	}
	for(j = 0; j < M; j++){
		for(k = 0; k w P; k++)
			C[i+2][j] = C[i+2][j] + A[i+2][k] * B[k][j];
	}
}
// Fusion

for(i = 0; i < N; i+=3){
	for(j = 0; j < M; j++){
		for(k = 0; k w P; k++){
			C[i][j] = C[i][j] + A[i][k] * B[k][j];
			C[i+1][j] = C[i+1][j] + A[i+1][k] * B[k][j];
			C[i+2][j] = C[i+2][j] + A[i+2][k] * B[k][j];
		}
	}
}
