# simulation_CPU
Un processeur simulé en C.<br>
Ce projet a pour but de simuler le comportement d'un CPU rudimentaire en C. Il dispose de toutes les briques de bases d'un CPU classique, il peut donc théoriquement réaliser n'importe quel calcul si on sait le piloter.
<br><br>
Par défaut le CPU est sur 16b mais il fonctionne sur des configurations <32 bits. Pour changer, il suffit de se rendre à la ligne 16 et remplacer NBITS par le nombre de bits voulus (>0 && <32).
<br><br>
Pour lancer la simulation :<br>
<code>gcc simulation_CPU.c</code><br><code>./a.out</code><br><br>
Le simulation dispose de 18 fonctionnalités :<br>
- Quitter : permet de fermer la simulation et de désallouer la mémoire<br>
- setValue(operande,int) : Initialisation du mot (mot de NBITS bits, codant un entier en Cà2) avec une valeur entière.<br>
- pass(alu,operande) : Stocke le paramètre dans le registre accumulateur<br>
- printing(alu) : affiche à l'écran le contenu de l'ALU<br>
- afficher toString(operande) : Retourne une chaîne de caractères décrivant les NBITS bits<br>
- afficher intValue(operande) : Retourne la valeur entière signée représentée par le mot (complément à 2).<br>
- afficher intValue(accu) : Retourne la valeur entière signée représentée par le mot (complément à 2).<br>
- nand(accu,operande) : effectue un nand entre le contenu de l'accumulateur et l'opérande.<br>
- add(accu,operande) : Additionne le paramètre au contenu de l'accumulateur (addition entière Cà2). Les indicateurs (flags) sont positionnés conformément au résultat de l'opération.<br>
- sub(accu,operande) : Idem que add mais soustrait (addition entière Cà2).<br>
- and(accu,operande) : idem nand mais pour l'opération logique and.<br>
- or(accu,operande) : idem nand mais pour l'opération logique or.<br>
- xor(accu,operande) : idem nand mais pour l'opération logique xor.<br>
- not(accu) : effectue l'opération not sur le contenu de l'accu.<br>
- opp(accu) : inverse le signe du nombre contenu dans l'accu.<br>
- shift(accu) : Décale le contenu de l'accumulateur de 1 bit vers la droite.<br>
- logicalShift(accu,int) : Décale le receveur de |n| positions. Le décalage s'effectue vers la gauche si n>0 vers la droite dans le cas contraire. C'est un décalage logique (pas de report du bit de signe dans les positions libérées en cas de décalage à droite). L'indicateur CF est positionné avec le dernier bit "perdu".<br>
- mul(accu,operande) : idem que pour add mais pour l'opération de multiplication.<br>
