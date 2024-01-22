type genre = Masculin | Feminin;;
type nombre = Singulier | Pluriel;;
type personne = Premiere | Seconde | Troisieme | Aucun ;;


type accord = {
	g : genre;
	nb : nombre;
	pers : personne;
};;
(*accord "par défaut" en quelque sorte.*)
let m_sing_trois = {g = Masculin; nb = Singulier; pers = Troisieme};;

(*type conjugaison = Present | Impft | Futur_s | Passe_s | P_q_p | Passe_c; (*1=présent; 2=imparfait; 3=futur simple; 4= passé simple; 5= pqp; 6= passé composé*) *)


(*
TODO : Ajouter les adverbes
TODO : prendre en compte les mot ambigus e.g. «le» qui est pronom COD et déterminant.
*)
type nature = 
	Determinant | 
	Nom |  
	Pronom | 
	Verbe |
	Adjectifs;;

(*
TODO : Créer un type "constructeur" de mot qui instancie un mot (e.g. manger) decliné avec
sa personne, son genre, son nombre. 
*)

type mot = {
	nat : nature;
	acc : accord;
	repr : string
};;

let new_mot (nat : nature) (g : genre) (nb : nombre) (pers : personne) (repr : string) =
	{nat; acc = {g ; nb; pers}; repr}
;;



let new_nom = new_mot Nom;;
let new_verbe = new_mot Verbe;;
let new_determinant = new_mot Determinant;;
let new_pronom = new_mot Pronom;;
let new_adjctif = new_mot Adjectifs;;

(*
TODO: faire un lexicaliseur pour le lexage des mots.
*)


(*

P V D N
D N V D N
V D N
P V N
D N V N
...
P V D N A
P V D A N
P V D A A N

Pour les phrases plus complexes, il faudra prendre en compte les propositions,
les groupes nonimaux... au lieu de modifier cette fonction.

On a pas vérifier tous les cas, penser à en ajouter, e.g. Determinant Determinant.
*)
let proposition_correcte (phrase : mot list) = match phrase with
	| [] -> true
	| t::r -> let rec aux (prec : mot) (reste : mot list) =
		match reste with
			| [] -> true
			| suiv::q -> (match suiv.nat with
				| Determinant -> prec.nat = Verbe
				(*Les pronoms sont valides quand le mot précédent n'est pas un nom*)
				| Pronom -> prec.nat <> Pronom
				| Nom ->
					prec.nat = Verbe || 
					(prec.nat = Determinant || prec.nat = Adjectifs) && suiv.acc = prec.acc 
				| Adjectifs -> (
					prec.nat = Nom ||
					prec.nat = Determinant ||
					prec.nat = Adjectifs)
					&& suiv.acc = prec.acc 
					
				| Verbe -> 
					(prec.nat = Pronom || prec.nat = Nom) && suiv.acc = prec.acc
				
				) && aux suiv q
	in aux t r
;;




(*
Nous travaillons sur la structure de phrase simple:
Sujet Verbe COD

pour détecter cette structure :

Sujets : (P) (D N) (D A N) etc  ex: "Je" "Un oiseau" "Le premier jeu"
Verbes : (V) (V V) "parlons" "a entendu"
COD : (D N) (D N A) 

*)
type fonction = Sujet | Verbe | ComplementObjetDirect

type blocphrase = {
	fonct : fonction;
	mots : mot list;
	acc : accord
};;

(* création d'un bloc *)
let creer_bloc (fo : fonction) (mo : mot list) (ac : accord) = {fonct = fo; mots = mo; acc = ac};;
 
(* Ajout d'un mot dans un bloc *)
let add_in_bloc (bloc : blocphrase) (mo : mot) = {fonct = bloc.fonct; mots = mo::bloc.mots; acc = mo.acc};;
(*
let test_accords_blocs bloc1 bloc2 = 
	match bloc1.acc1,bloc2.acc2 with
	| {_;_;acc1},{_;_;acc2}->acc1=acc2 
;;*)
(*
let decoupe_phrase (phrase : mot list) = (* Non achevée*)
	let bloc_verbe = creer_bloc Verbe [] m_sing_trois (* Initialisation des blocs *)
	let bloc_sujet = creer_bloc Sujet [] m_sing_trois
	let bloc_cod = creer_bloc ComplementObjetDirect [] m_sing_trois

	let rec aux (phrase : mot list) (blocs : blocphrase list) = 
		match phrase with
			|	[]->blocs
  		| mot::reste -> 
				match mot.nat with
					| Verbe -> aux reste ({Verbe,[mot],mot.acc}::blocs)
*)
(*
concept:

tant que il y a des mots :
	si le mot suivant correspond au bloc courant:
		insérer le mot dans le bloc courant
	sinon :
		fermer le bloc, l'ajouter à la liste et en ouvrir un autre
si il n'y a plus de mots, fermer le bloc courant
vérifier la cohérence interne de chaque bloc : donc les accords 
vérifier la structure de la phrase

				/\
			/	| \
		/	  |  \
	/			. 	\
/____________\


Faite gaffe avec les blocs, ils sont parfois imbriqués e.g.

Le chat de ma voisine fait du ski

«de ma voisine» est ici imbriqué dans Le chat <... > fait du ski.

Ça serait mieux de prendre en compte les groupes nominaux, les propositions...

Ça rend la chose plus simple à parser:
	- ... <NOM> <PRÉPOSITION> ... => complément du nom
	- ... <NOM> <PRONOM-RELATIF> ... => proposition subordonnée relative
	- ... <CONJONCTION DE COORDINATION> ..., fin de proposition
	- ...

Ha, et faites gâffe le && est prioritaire sur || (dans le doute mettez des parenthèses).
*)



(*
Écrire des funs de test c'est plus propre ^^.	 
OCaml vient avec des outils pour faire ça, mais pour garder le code simple pour l'instant on va tous faire avec des funs.
*)

let test_proposition_correcte =
	let je = new_pronom Masculin Singulier Premiere "Je" in
	let mange = new_verbe Masculin Singulier Premiere "mange" in
	let une = new_determinant Feminin Singulier Troisieme "une" in
	let pomme = new_nom Feminin Singulier Troisieme "pomme" in
	let verte = new_adjctif Feminin Singulier Troisieme "verte" in
	let phrase1 = [je; mange; une; pomme; verte] in
	let phrase2 = [je; mange; verte; une; pomme] in
	let phrase3 = [je; verte; mange; une; pomme] in
	proposition_correcte phrase1 &&
	not (proposition_correcte phrase2) &&
	not (proposition_correcte phrase3)
;;


(*Retourne le résulat du test pour des utilisation ultérieur*)
(*le %! il est là pour des trucs de sécurité lié au buffer blablabla...*)
let print_test (num : int) (nom : string) (test : bool) =
	Printf.printf "[%d] Test de de «%s» : %s ! \n%!" num nom (if test then "SUCCÈS" else "ÉCHEC");
	test
;; 

(*teste tous le projet*)
let tester_projet = if print_test 1 "proposition_correcte" test_proposition_correcte (*&& print_test 2 ... && print_test 3 ...*)
	then (Printf.printf "\nTous les tests ont été effectués avec succès !\n%!" ; exit 0)
	else (Printf.printf "Il y a eu des erreurs dans les tests...\n%!" ; exit 1)
;;

(*Pensez à compiler avec ocamlc -o grammaire grammaire.ml*)
