type genre = Masculin | Feminin;;
type nombre = Singulier | Pluriel;;
type personne = Premiere | Seconde | Troisieme | None ;;


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
let new_determinant = new_mot Determinant
let new_pronom = new_mot Pronom;;
let new_adjctif = new_mot Adjectifs;;

(*
TODO: faire un lexicaliseur pour le lexage des mots.
*)

let je = new_pronom Masculin Singulier Premiere "Je";;
let mange = new_verbe Masculin Singulier Premiere "mange";;
let une = new_determinant Feminin Singulier Troisieme "une"
let pomme = new_nom Feminin Singulier Troisieme "pomme";;
let verte = new_adjctif Feminin Singulier Troisieme "verte";;

let phrase1 = [je; mange; une; pomme; verte];;
let phrase2 = [je; mange; verte; une; pomme];;
let phrase3 = [je; verte; mange; une; pomme];;

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
*)

(*
On a pas vérifier tous les cas, pensé à en ajouter, e.g. Determinant Determinant.
*)
let proposition_correcte (phrase : mot list) = match phrase with
	| [] -> true
	| t::r -> let rec aux (prec : mot) (reste : mot list) =
		match reste with
			| [] -> true
			| suiv::q -> (match suiv.nat with
				(*Les déterminants sont toujours valides*)
				| Determinant -> prec.nat <> Pronom 
				(*Les pronoms sont valides quand le mot précédent n'est pas un nom (pour l'instant !)*)
				| Pronom -> prec.nat <> Nom && prec.nat <> Pronom 
				| Nom -> (
					prec.nat = Verbe || 
					prec.nat = Determinant ||
					prec.nat = Adjectifs && suiv.acc = prec.acc 
					)
				| Adjectifs -> (
					prec.nat = Nom ||
					prec.nat = Determinant ||
					prec.nat = Adjectifs && suiv.acc = prec.acc 
					)
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
	foncti : fonction;
	mots : mot list;
	acc : accord
};;

let test_accords_blocs bloc1 bloc2 = 
	match bloc1,bloc2 with
	| {_;_;acc1},{_;_;acc2}->acc1=acc2 
;;

let decoupe_phrase (phrase : mot list) = 
	let rec aux (phrase : mot list) (blocs : blocphrase list) = 
		match phrase with
			|	[]->blocs
  		| mot::reste -> 
				match mot.nat with
					| Verbe -> aux reste ({Verbe,[mot],mot.acc}::blocs)

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
*)
