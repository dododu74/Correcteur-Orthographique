type genre = Masculin | Feminin;;
type nombre = Singulier | Pluriel;;
type personne = Premiere | Seconde | Troisieme;;


type accord = {
	g : genre;
	nb : nombre;
	pers : personne;
};;
(*accord "par défaut" en quelque sorte.*)
let m_sing_trois = {g = Masculin; nb = Singulier; pers = Troisieme};;

(*type conjugaison = Present | Impft | Futur_s | Passe_s | P_q_p | Passe_c; (*1=présent; 2=imparfait; 3=futur simple; 4= passé simple; 5= pqp; 6= passé composé*) *)


(*
TODO : Ajouter les adjectifs, et les adverbes

*)
type nature = 
	Determinant | 
	Nom |  
	Pronom | 
	Verbe;;

(*
Créer un type "constructeur" de mot qui instancie un mot (e.g. manger) decliné avec
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

(*
TODO: faire un lexicaliseur pour le lexage des mots.
*)

let je = new_pronom Masculin Singulier Premiere "Je";;
let mange = new_verbe Masculin Singulier Premiere "mange";;
let une = new_determinant Feminin Singulier Troisieme "une"
let pomme = new_nom Feminin Singulier Troisieme "pomme";;

let phrase = [je; mange; une; pomme];;

(*
P V D N
D N V D N
V D N
P V N
D N V N
...

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
					prec.nat = Determinant && suiv.acc = prec.acc)
				| Verbe -> 
					(prec.nat = Pronom || prec.nat = Nom) && suiv.acc = prec.acc
				) && aux suiv q
	in aux t r
;;
