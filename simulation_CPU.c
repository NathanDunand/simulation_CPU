/*
 * -------------------------- TP du module Archi -------------------------
 *
 * ATTENTION : un outil de d�tection de plagiat logiciel sera utilis� lors de la correction, vous avez donc tout int�r�t � effectuer un travail PERSONNEL
 *
 * Un mot/registre de NBITS bits (par d�faut NBITS=16) est repr�sent� par un tableau d'entiers �gaux � 0 ou 1.
 * Une ALU est repr�sent�e par une structure ALU, avec registre accumulateur et registre d'�tat.
 * Un CPU (tr�s tr�s simplifi�) est repr�sent� par une ALU et quelques registres n�cessaires pour stocker les r�sultats interm�diaires.
 *
 * Certaines fonctions vous sont fournies, d'autres sont � implanter ou � compl�ter, de pr�f�rence dans l'ordre o� eles sont indiqu�es.
 * Il vous est fortement conseill� de lire attentivement l'ensemble des commentaires.
 *
 * Parmi les op�rations arithm�tiques et logiques, seules 4 op�rations de base sont directement fournies par l'ALU, les autres doivent �tre d�crites comme des algorithmes
 * travaillant � l'aide des op�rateurs de base de l'ALU simplifi�e et pouvant utiliser les registres du CPU.
 *
 * La fonction main() vous permet de tester au fur et � mesure les fonctions que vous implantez.
 *
 * ----------------------------------------------------------------------------------------------
 *
 * author: B. Girau
 * version: 2018-19
 */
#include <stdio.h>
#include <stdlib.h>

#define NBITS 16  // attention, votre programme doit pouvoir �tre adapt� � d'autres tailles juste en modifiant la valeur de cette constante
// en ayant toujours NBITS < 32

/////////////////////////////////////////////////////////
// d�finition de types
/////////////////////////////////////////////////////////

typedef struct {
	int* accu;
  int* flags; // indicateurs ZF CF OF NF
} ALU;

typedef struct {
	ALU alu;
	int* R0;
	int* R1;
	int* R2;
} CPU;

/////////////////////////////////////////////////////////
// fonctions d'initialisation
/////////////////////////////////////////////////////////

/*
 * allocation d'un mot entier de NBITS bits initialis� � 0
 */
int* word() {
	int* tab;
	int i;
	tab=(int*)malloc(NBITS*sizeof(int));
	for(i=0;i<NBITS;i++) tab[i]=0;
  // poids faible : tab[0]
  // poids fort : tab[NBITS-1]
		return tab;
}

/*
 * Initialisation du mot (mot de NBITS bits, codant un entier en C�2) avec une valeur enti�re.
 */
void setValue(int* word,int n) {
  //int n_low = n & 0x7FFFFFFF;
  // revient � mettre � 0 le bit de poids fort en 32 bits
  // on peut alors travailler sur la partie positive du codage de n
  // remarque : si n est bien codable en Ca2 sur NBITS, et si n est n�gatif, on r�cup�re quand m�me le codage de n sur NBITS en Ca2 en prenant les NBITS de poids faible de n_low

	
  // � compl�ter
  int m=n;//je ne travaille pas directement sur n
  //d'abord coder la valeur abs
  for(int i=0;i<NBITS-1;i++){
    if(m%2==0){//si n pair
    	word[i]=0;
    }else{//n impair
    	word[i]=1;
    }
    m/=2;
}
  //CA1 que quand n n�gatif
if(n<0){
	word[NBITS-1]=1;
	for(int i=0;i<NBITS-1;i++){
		if(word[i]==0){
			word[i]=1;
		}else{
			word[i]=0;
		}
	}
    //ajouter 1
	int retenue=1;
	for(int i=0;i<NBITS-1;i++){
		if(word[i]==0 && retenue==0){
			word[i]=0;
			retenue=0;
		}else if(word[i]==0 && retenue==1){
			word[i]=1;
			retenue=0;
		}else if(word[i]==1 && retenue==1){
			word[i]=0;
			retenue=1;
		}
	}
  }else{//bit de poids fort quand n positif
  	word[NBITS-1]=0;
  }
}

/*
 * instanciation d'un mot de NBITS bits initialis� avec la valeur n
 */
int* initWord(int n) {
	int* tab=word();
	setValue(tab,n) ;
	return tab;
}

/*
 * Initialisation du mot (mot de NBITS bits) par recopie des bits du mot en param�tre.
 */
void copyValue(int* word,int* src) {
	for(int i=0;i<NBITS;i++){
		word[i]=src[i];
	}
}

/*
 * instanciation d'un mot de NBITS bits initialis� par recopie d'un mot
 */
int* copyWord(int* src) {
	int* tab=word();
	copyValue(tab,src) ;
	return tab;
}

/*
 * initialise l'ALU
 */
ALU initALU() {
	ALU res;
	res.accu=word();
	res.flags=(int*)malloc(4*sizeof(int));
	return res;
}

/*
 * initialise le CPU
 */
CPU initCPU() {
	CPU res;
	res.alu=initALU();
	res.R0=(int*)malloc(NBITS*sizeof(int));
	res.R1=(int*)malloc(NBITS*sizeof(int));
	res.R2=(int*)malloc(NBITS*sizeof(int));
	return res;
}

/////////////////////////////////////////////////////////
// fonctions de lecture
/////////////////////////////////////////////////////////

/*
 * Retourne la valeur enti�re sign�e repr�sent�e par le mot (compl�ment � 2).
 */    
/*int intValue(int* word){
	int value=0;

	if(word[NBITS-1]==1){//word n�gatif
		for(int i=NBITS-2;i>=0;i--) {
			if(word[i]==1) {//inversion
				word[i]=0;
			} else {
				word[i]=1;
			}
		}

		//+1
		int retenue=1;
		for(int i=0;i<NBITS-1;i++){
			if(word[i]==0 && retenue==0){
				word[i]=0;
				retenue=0;
			}else if(word[i]==0 && retenue==1){
				word[i]=1;
				retenue=0;
			}else if(word[i]==1 && retenue==1){
				word[i]=0;
				retenue=1;
			}
		}
		printf("%i\n", value);
	}

	return value;
}*/
int intValue(int* word) {
	/*int copy[NBITS];
	copyValue(copy,word);*/
	int copy[NBITS-1];
	for(int i=0;i<NBITS;i++) {
		copy[i]=word[i];
	}


  /*printf("Base\n");
  for(int i=NBITS-1;i>=0;i--){
      printf("%i", copy[i]);//1
  }printf("\n");*/

	int value=0;
	int temp=0;

  if(copy[NBITS-1]==0){//word positif
  	for(int i=NBITS-2;i>=0;i--){
  	if(copy[i]==1){
  		temp=1;
  		if(i>1){
          for(int j=0;j<i;j++){//calcul de la puissance
          	temp*=2;
          }
    	}else if(i==1){
      	temp=2;
    	}else if(i==0){
      	temp=1;
    	}
    	value+=temp;
  }
}
  }else{//word n�gatif
    //CA1
  	for(int i=NBITS-2;i>=0;i--){
  		if(word[i]==0){
  			copy[i]=1;
  		}
  		if(word[i]==1) {
  			copy[i]=0;
  			//printf("i %i\n copy %i",i,copy[i]);
  		}
  	}

    //+1
  	int retenue=1;
  	for(int i=0;i<NBITS;i++){
  		if(copy[i]==0 && retenue==0){
  			copy[i]=0;
  			retenue=0;
  		}else if(copy[i]==0 && retenue==1){
  			copy[i]=1;
  			retenue=0;
  		}else if(copy[i]==1 && retenue==1){
  			copy[i]=0;
  			retenue=1;
  		}
  	}

    /*printf("+1\n");
    for(int i=NBITS-1;i>=0;i--){
      printf("%i", word[i]);//1
    }printf("\n");*/

    //conversion en d�cimal
  	for(int i=NBITS-2;i>=0;i--){
  		if(copy[i]==1){
  			temp=1;
  			if(i>1){
          for(int j=0;j<i;j++){//calcul de la puissance
          	temp*=2;
          }
      }else if(i==1){
      	temp=2;
      }else if(i==0){
      	temp=1;
      }
      value+=temp;
  }
}
    if(value==0 && copy[NBITS-1]==1){//cas particulier on est � la plus petite valeur
    	temp=1;
      for(int i=0;i<NBITS;i++){//calcul de la puissance
      	temp*=2;
      }
      value=temp;
  }
  value*=-1;
}
return value;
}

/*
 * Retourne une cha�ne de caract�res d�crivant les NBITS bits
 */
char* toString(int* word) {
	int i,j=0;
	char* s=(char*)malloc((2+NBITS)*sizeof(char));
	for (i=NBITS-1;i>=0;i--) {
		if (word[i]==1) s[j]='1';
		else s[j]='0';
		j++;
	}
	s[j]='\0';
	//printf("intValue %i\n", intValue(word));
	return s;
}

/*
 * Retourne l'�criture des indicateurs associ�s � l'ALU.
 */
char* flagsToString(ALU alu) {
	char *string=(char*)malloc(10*sizeof(char));
	sprintf(string,"z%dc%do%dn%d",alu.flags[0],alu.flags[1],alu.flags[2],alu.flags[3]);
	return string;
}

/*
 * affiche � l'�cran le contenu d'une ALU
 */
void printing(ALU alu) {
  // � priori fonctionnelle, � tester pour les accu
  //affichage des flags de l'ALU
	char* stringFlags=(char*)malloc(10*sizeof(char));
	stringFlags=flagsToString(alu);
	printf("%s\n", stringFlags);

  //affichage de l'accu
	/*printf("test\n");
	for(int i=NBITS-1;i>=0;i--){
		printf("%i", alu.accu[i]);
	}
	printf("\n");*/


	printf("accu bin : %s \n", toString(alu.accu));
	printf("accu dec : %i \n", intValue(alu.accu));

	
}

/////////////////////////////////////////////////////////
// fonctions de manipulations �l�mentaires
/////////////////////////////////////////////////////////

/*
 * Mise � la valeur b du bit sp�cifi� dans le mot
 */
void set(int* word,int bitIndex,int b) {
	if ((bitIndex > NBITS-1) || (bitIndex < 0)) 
		printf("valeur d'index incorrecte\n");
	word[bitIndex] = b ;
}

/*
 * Retourne la valeur du bit sp�cifi� dans le mot
 */
int get(int* word,int bitIndex) {
	if ((bitIndex > NBITS-1) || (bitIndex < 0)) 
		printf("valeur d'index incorrecte\n");
	return word[bitIndex] ;
}

/*
 * Positionne l'indicateur ZF en fonction de l'�tat de l'accumulateur
 */
void setZ(ALU alu) {
	//� priori fonctionnel
	if(intValue(alu.accu)==0){
		alu.flags[0]=1;
	} else {
		alu.flags[0]=0;
	}
}

/////////////////////////////////////////////////////////
// op�rateurs de base de l'ALU
// IMPORTANT : les indicateurs doivent �tre mis � jour
/////////////////////////////////////////////////////////

/*
 * Stocke le param�tre dans le registre accumulateur
 */
void pass(ALU alu,int* B) {
	for(int i=NBITS-1;i>=0;i--){
		alu.accu[i]=B[i];
	}

  //mise � jour des flags
	setZ(alu);
	alu.flags[1]=0;
	alu.flags[2]=0;
	if(intValue(alu.accu)<0) {
		alu.flags[3]=1;
	} else {
		alu.flags[3]=0;
	}
}

/*
 * Effectue un NAND (NON-ET) entre le contenu de l'accumulateur et le param�tre.
 */
void nand(ALU alu,int* B) {
  // � compl�ter
	for(int i=0;i<NBITS;i++) {
		if(alu.accu[i]==1 && B[i]==1) {
			alu.accu[i]=0;
		} else {
			alu.accu[i]=1;
		}
	}

  //mise � jour des flags
	setZ(alu);
	if(intValue(alu.accu)<0) {
		alu.flags[3]=1;
	} else {
		alu.flags[3]=0;
	}
	alu.flags[1]=0;
	alu.flags[2]=0;
}

/*
 * D�cale le contenu de l'accumulateur de 1 bit vers la droite
 */
void shift(ALU alu) {
  // � compl�ter
	for(int i=0;i<NBITS;i++) {
		if(i!=NBITS-1) {
			set(alu.accu,i,get(alu.accu,i+1));
		} else {
			set(alu.accu,i,0);
		}
	}

  //mise � jour des flags
	setZ(alu);
	if(intValue(alu.accu)<0) {
		alu.flags[3]=1;
	} else {
		alu.flags[3]=0;
	}
	alu.flags[1]=0;
	alu.flags[2]=0;
}

/*
 * module Full Adder : a+b+c_in = s + 2 c_out
 * retourne un tableau contenant s et c_out
 */
int* fullAdder(int a,int b,int c_in) {
	int* res=(int*)malloc(2*sizeof(int));
  // � compl�ter
  //c_in retenue entrante
  //c_out retenue sortante
	int c_out=0;
	int s=0;
  if(c_in==0){//pas de retenue entrante
  	if(a==0 && b==0) {
  		c_out=0;
  		s=0;
  	}
  	if( (a==0 && b==1) || (a==1 && b==0) ) {
  		c_out=0;
  		s=1;
  	}
  	if(a==1 && b==1) {
  		c_out=1;
  		s=0;
  	}
  } else {//retenue entrante
  	if(a==0 && b==0) {
  		c_out=0;
  		s=1;
  	}
  	if( (a==0 && b==1) || (a==1 && b==0) ) {
  		c_out=1;
  		s=0;
  	}
  	if(a==1 && b==1) {
  		c_out=1;
  		s=1;
  	}
  }
  
  res[0]=s;
  res[1]=c_out;
  return res;
}

/*
 * Additionne le param�tre au contenu de l'accumulateur (addition enti�re C�2).
 * Les indicateurs sont positionn�s conform�ment au r�sultat de l'op�ration.
 */
void add(ALU alu,int* B) {
	int c_in=0;
	int* res=malloc(2*sizeof(int));
	int ancienAccu=intValue(alu.accu);
	for(int i=0;i<NBITS;i++) {
		res=fullAdder(alu.accu[i], B[i], c_in);
		alu.accu[i]=res[0];
		//printf("%i", res[1]);
		c_in=res[1];
	}

  //mise � jour des flags
	alu.flags[0]=alu.flags[1]=alu.flags[2]=alu.flags[3]=0;
	setZ(alu);
	if(res[1]==1) {//retenue sortante
		alu.flags[1]=1;//cf � 1
	}

	//signe des op�randes et du r�sultat diff�rent -> OF
	if(ancienAccu>0 && intValue(B)>0) {//addition de deux positifs -> positif sans overflow
		if(intValue(alu.accu)<=0) {
			//overflow
			alu.flags[2]=1;
		}
	}

	if(ancienAccu<0 && intValue(B)<0) {//addition de deux n�gatifs -> n�gatif sans overflow
		if(intValue(alu.accu)>=0) {
			//overflow
			alu.flags[2]=1;
		}
	}

	alu.flags[3]=alu.accu[NBITS-1];
	
}

////////////////////////////////////////////////////////////////////
// Op�rations logiques :
////////////////////////////////////////////////////////////////////

/*
 * N�gation.
 */
void not(CPU cpu) {
  // � compl�ter
	nand(cpu.alu, cpu.alu.accu);
	//flags
	cpu.alu.flags[0]=cpu.alu.flags[1]=cpu.alu.flags[2]=cpu.alu.flags[3]=0;
	setZ(cpu.alu);
	cpu.alu.flags[3]=cpu.alu.accu[NBITS-1];
}

/*
 * Et.
 */
void and(CPU cpu,int* B) {
  // � compl�ter
	nand(cpu.alu,B);//nand(x,y)
	nand(cpu.alu,cpu.alu.accu);
	
	setZ(cpu.alu);
	cpu.alu.flags[1]=cpu.alu.flags[2]=0;
	cpu.alu.flags[3]=cpu.alu.accu[NBITS-1];
}


/*
 * Ou.
 */
void or(CPU cpu,int* B) {
  // � compl�ter
	nand(cpu.alu, cpu.alu.accu);//nand(x,x)
	copyValue(cpu.R0, cpu.alu.accu);//R0 contient nand(x,x)

	copyValue(cpu.alu.accu, B);//sauvegarde de y
	nand(cpu.alu,B);//nand(y,y)

	nand(cpu.alu, cpu.R0);//nand(nand(x,x), nand(y,y))

	setZ(cpu.alu);
	cpu.alu.flags[1]=cpu.alu.flags[2]=0;
	cpu.alu.flags[3]=cpu.alu.accu[NBITS-1];
}

/*
 * Xor.
 */
void xor(CPU cpu,int* B) {
  // � compl�ter

	copyValue(cpu.R1, cpu.alu.accu);//copy de l'accu

	or(cpu, B);//a or b
	copyValue(cpu.R2, cpu.alu.accu);//R2 contient a or b
	//dest, source

	copyValue(cpu.alu.accu, cpu.R1);//on remet dans accu R1
	and(cpu, B);//a and b

	not(cpu);//not(a and b)

	and(cpu, cpu.R2);//and final

	setZ(cpu.alu);
}

/*
 * D�cale le receveur de |n| positions.
 * Le d�calage s'effectue vers la gauche si n>0 vers la droite dans le cas contraire.
 * C'est un d�calage logique (pas de report du bit de signe dans les positions 
 * lib�r�es en cas de d�calage � droite).
 * L'indicateur CF est positionn� avec le dernier bit "perdu".
 */
void logicalShift(CPU cpu,int n) {
  // � compl�ter
	if(n>0) {//vers la gauche
		for(int i=0;i<n;i++) {
			add(cpu.alu, cpu.alu.accu);
		}
	} else {//vers la droite
		for(int i=n;i<0;i++) {
			/*for(int i=0;i<NBITS-1;i++) {
				if(i!=NBITS-1) {
					set(cpu.alu.accu,i,get(cpu.alu.accu,i+1));
				} else {
					set(cpu.alu.accu,i,0);
				}
			}*/
			shift(cpu.alu);
		}
	}
	setZ(cpu.alu);
}

/////////////////////////////////////////////////////////
// Op�rations arithm�tiques enti�res
/////////////////////////////////////////////////////////

/*
 * Oppos�.
 */
void opp(CPU cpu) {
  // � compl�ter
	not(cpu);
	setValue(cpu.R0,1);//R0 = 1
	add(cpu.alu, cpu.R0);
	
	setZ(cpu.alu);
	cpu.alu.flags[1]=cpu.alu.flags[2]=0;
	cpu.alu.flags[3]=cpu.alu.accu[NBITS-1];
}

/*
 * Soustraction.
 */
void sub(CPU cpu,int* B) {
  // � compl�ter

	copyValue(cpu.R1, cpu.alu.accu);//copie de l'accu dans R1
	copyValue(cpu.alu.accu, B);//copie de B dans accu pour faire opp()
	opp(cpu);//-cpu.alu.accu => -B
	copyValue(B, cpu.alu.accu);//B contient -B
	copyValue(cpu.alu.accu, cpu.R1);//accu contient a
	add(cpu.alu, B);//a + -b

	setZ(cpu.alu);
}

/*
 * Multiplication.
 */
void mul(CPU cpu,int* B) {
  // � compl�ter
	setValue(cpu.R0,0);
	copyValue(cpu.R1, cpu.alu.accu);//m, R1 prend la valeur de l'op�rande a

	for(int i=0;i<NBITS-1;i++) {
		if(get(B,i)==1) {
			copyValue(cpu.alu.accu, cpu.R0);
			add(cpu.alu, cpu.R1);
			copyValue(cpu.R0, cpu.alu.accu);
		}
		copyValue(cpu.alu.accu, cpu.R1);
		logicalShift(cpu,1);
		copyValue(cpu.R1, cpu.alu.accu);
	}
	copyValue(cpu.alu.accu, cpu.R0);

	setZ(cpu.alu);
	cpu.alu.flags[3]=cpu.alu.accu[NBITS-1];
}

/////////////////////////////////////////////////////////
// Programme de test
/////////////////////////////////////////////////////////

int main(int argc,char *argv[]) {

  /*fait par moi*/
  /*for(int i=NBITS-1;i>0;i++){
    printf("%i", );
  }*/

  /*
    Ce programme est fourni � titre d'exemple pour permettre de tester simplement vos fonctions.
    Il vous est bien entendu possible de le modifier/compl�ter, ou encore d'�crire vos propres fonctions de test.
   */

	int* operand;
	ALU alu;
	CPU cpu;

	int chosenInt,integer ;
	int go_on = 1 ;

	char* menu =     
	"              Programme de test\n\n0  Quitter\n1  setValue(operande,int)\n2  pass(alu,operande)\n3  printing(alu)\n4  afficher toString(operande)\n5  afficher intValue(operande)\n6  afficher intValue(accu)\n7  accu=nand(accu,operande)\n8  accu=add(accu,operande)\n9  accu=sub(accu,operande)\n10  accu=and(accu,operande)\n11 accu=or(accu,operande)\n12 accu=xor(accu,operande)\n13 accu=not(accu)\n14 accu=opp(accu)\n15 accu=shift(accu)\n16 accu=logicalShift(accu,int)\n17 accu=mul(accu,operande)\n\n" ;

	char* invite = "--> Quel est votre choix  ? " ;

	printf("%s",menu) ; 

	operand=word();
	cpu=initCPU();
	alu=cpu.alu;

	while (go_on==1) {
		printf("%s",invite);
		scanf("%d",&chosenInt);
		switch (chosenInt) {
			case 0 : 
			go_on = 0 ;
			break ;
			case 1 :
			printf("Entrez un nombre :"); 
			scanf("%d",&integer);
			setValue(operand,integer);
			break ;
			case 2 : 
			pass(alu,operand);
			break ;
			case 3 : 
			printing(alu);
			break ;
			case 4 : 
			printf("%s\n",toString(operand));
			break ;
			case 5 : 
			printf("intValue(operand)=%d\n",intValue(operand));
			break ;
			case 6 : 
			printf("intValue(accu)=%d\n",intValue(alu.accu));
			break ;
			case 7 : 
			nand(alu,operand);
			printf("apres nand(), accu = ");
			printing(alu);
			break ;
			case 8 : 
			add(alu,operand);
			printf("apres add(), accu = ");
			printing(alu);
			break ;
			case 9 : 
			sub(cpu,operand);
			printf("apres sub(), A = ");
			printing(alu);
			break ;
			case 10 : 
			and(cpu,operand);
			printf("apres and(), A = ");
			printing(alu);
			break ;
			case 11 : 
			or(cpu,operand);
			printf("apres or(), A = ");
			printing(alu);
			break ;
			case 12 : 
			xor(cpu,operand);
			printf("apres xor(), A = ");
			printing(alu);
			break ;
			case 13 : 
			not(cpu);
			printf("apres not(), A = ");
			printing(alu);
			break ;
			case 14 : 
			opp(cpu);
			printf("apres opp(), A = ");
			printing(alu);
			break ;
			case 15 : 
			shift(alu);
			printf("apres shift(), A = ");
			printing(alu);
			break ;
			case 16 : 
			printf("Entrez un entier :") ;
			scanf("%d",&integer);
			logicalShift(cpu,integer);
			printf("apres logicalshift(%d), A = ",integer);
			printing(alu);
			break ;
			case 17 : 
			mul(cpu,operand);
			printf("apres mul(), A = ");
			printing(alu);
			break ;
			default : 
			printf("Choix inexistant !!!!\n");
			printf("%s",menu);
		}
	}
	printf("Au revoir et a bientot\n");
	return 0;
}



