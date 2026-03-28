#use "tri.ml";;

(*** Retourne un couple donné et le nombre de ses apparitions dans une liste **)

let  get_nb_element(e, l : fich * fich list) : count =

  
  if empty l
  then failwith "ERROR (compare_el_list) : Liste d'entrée vide"
  else
    let (a, b) = e
    and  f : fich list ref = ref (sort compare_by_couple l)
    and  n : int ref = ref 0
    in
    while not(empty (!f)) && (a <> user (!f) || b <> pw (!f))
    do
      f := next_couple(!f);
    done;
    
      while not(empty (!f)) && (a = user (!f) && b = pw (!f))           
      do        
        n := !n + 1;       
        f := next_couple(!f);        
      done;
      (e, !n)
;;


(*** Retourne l'ensemble des couples qui existe en double
     dans une liste ***)

let  get_double(l : fich list) : count list =
  
  if  empty l
  then failwith "ERROR (get_doub) : Liste d entree vide"
  else
    
    let f : fich list ref = ref (sort compare_by_couple l)
    and count : count list ref = ref []
    in
    
    while not(empty !f)
    do
      
      let n : int ref = ref 0
      and c : fich ref = ref (fst !f)
      in
      
          while not(empty !f) && (!c = fst (!f))
          do
            n := !n + 1;
            f := next_couple(!f);
          done;
          if !n = 1
          then ()
          else  count := (!c, !n) :: !count
    done;
    !count
    
;;


(**** Retourne un element (user ou mdp) qui existe n fois
      avec son autre element associé (user ou mdp) en liste
      la liste d entrée doit etre triée
      par couple si on cherche des mdps pour user
      et par mdp si on cherche des users pour un mdp
 *****)


let get_element_doub_by_element (a : fich list -> string)
      (b : fich list -> string) (l: fich list) (u : string)  :
      string list =

  if empty l
  then failwith ("ERROR <get_user_pw_doub> : Liste d'entrée vide")
  else
    
    let f : fich list ref = ref l
    and result : string list ref = ref []
    in

    while not(empty !f) && a (!f) <> u
    do  
      f := next_couple(!f);
    done;
    
    while not(empty !f) && a (!f) = u          
    do

      if empty (!result) ||  b(!f) <> fst(!result)         
      then
        (
        result := b(!f) :: !result;
        f := res(!f);
        )
      else
        f := next_couple(!f);
      
    done;    
    u :: !result
;;

(*** Retourne une liste sans doublons ***)
let rec aux_get_list_out_double(f, e, l : fich list * fich * fich list)
        : fich list =
  
  if empty (next_couple f) && fst f = e
  then l
  else
    if empty (next_couple f) && fst f <> e
    then fst f :: l
    else
      if fst f = fst (next_couple f)
      then aux_get_list_out_double(next_couple(f), fst f, l)
      else fst f :: aux_get_list_out_double(next_couple(f), fst f, l)
;;

let rec get_list_out_double(li : fich list) : fich list =

  if empty li
  then failwith "ERROR <get_list_out_double> : Liste d'entrée vide"
  else

    let f : fich list  =  (sort compare_by_couple li) in
    
    if empty(next_couple f)
    then f
    else
      if fst f = fst(next_couple(f))
         && empty(next_couple(next_couple(f))) 
      then aux_get_list_out_double(f, fst f, [fst f])
      else aux_get_list_out_double(f, ("",""), [])
;;

(*** Teste pour un utilisateur si les mots de passe
     sont identique.***)

let rec aux_identiq_psw(l, b : string list * bool) : bool =
  if empty (res(res l))
  then b
  else
    if fst l = fst (res l)
    then  aux_identiq_psw(res l, true)
    else false
;;

let rec identiq_psw(l : string list) : bool =

  if empty (l)
  then failwith "ERROR <identiq_psw> : Liste d'entrée vide"
  else aux_identiq_psw(l, false)
;;

(*******************************************************************************)
                        (** LES MOTS DE PASSES **)

(*** Prend les mots de passe les plus connus et
     Retourne les mots de passe hachés ***)

let rec aux_get_hashs(f : string list) : fich list =
  if empty f
  then []
  else
    if check_mdp(fst f)
    then (hash (fst f)) :: aux_get_hashs(res f)
    else aux_get_hashs(res f)
;;

    
let rec get_hashs(f : string list) : fich list =
  if empty f
  then failwith "ERROR <get_hashs> : Liste d'entrée vide"
  else aux_get_hashs(f)
;;
