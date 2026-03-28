#use "tools.ml";;
type fich = (string * string);;
type usuel = string list ;;
type count = (fich * int);;

(** test la liste est vide **)
let empty(l : 'a list) : bool =
  l = []
;;

(** Avoir le premier element de la list **)
let fst(l : 'a list) : 'a =
    if empty l
    then failwith "ERROR <fst> : Liste vide "
    else List.hd l
;;

(** Avoir le reste de la liste **)

let res(l : 'a list) : 'a list =
  if empty l
  then failwith "ERROR <res> : Liste vide "
  else List.tl l
;;



(** Avoir le premier user (premier element de la list)**)
let user(l : ('a * 'b) list) : string =
  if empty l
  then failwith "ERROR <user>: Liste vide "
  else
    let (a, b) = List.hd l in
    a
;;

(** Avoir le premier mot de passe (deuxi�me element de la list)**)
let pw(l : ('a * 'b) list) : string =
  if empty l
  then failwith "ERROR <pw>: Liste vide "
  else
    let (a, b) = List.hd l in
    b
;;

(** Avoir le prochain couple user mot de passe **)
let next_couple (l : 'a list) : 'a list =
  if empty l
  then failwith "ERROR <next_couple> : Liste vide"
  else List.tl l
;;

(** Donne une liste sans élément (mdp ou user) identiq à la suite **)

let next_element (l : 'a list) (e : 'a list -> string) : 'a list =
  if empty l then
    failwith "ERROR <next_element> : Liste d'entrée vide"
  else
    let rec aux current =
      if empty current || empty (next_couple current) then
        next_couple current
      else if e current = e (next_couple current) then
        aux (next_couple current)
      else
        next_couple current
    in
    aux l
;;


(** Fonction qui transforme la liste de couple en une seule list **)
let rec couple_to_list(f : fich list) : usuel list =
  if empty (f)
  then []
  else
    let (a,b) = List.hd f in
    [a; b] :: couple_to_list(List.tl f)
;;

(** check si un element existe dans une string list **)
let rec exist(l, e : string list * string) : bool =

  if empty l
  then false
  else
    if e = List.hd l
    then true
    else exist (List.tl l, e)
;;


(** Prend un mots de passe  et
    Retourne le mot de passe hachés ***)
let hash(m : string) : fich =
  (hash_password(m), m)
;;


(** Verfie si un mot de passe est compris entre '!' et '~' **)
let check_char(m, n : string * int) : bool =

  let result : bool ref = ref true
  in
  for i = 0 to n - 1
  do
    if m.[i] < '!' || m.[i] > '~'
    then
        result := false;
  done;
  !result
;;

(** Verifie si un mot de passe est valide **)
let check_mdp(m : string) : bool =

  let n : int = (String.length m) in
  if n < 6 || n > 128
  then false
  else check_char(m, n)
;;


let time f x =
  let t = Sys.time() in
  let fx = f x in
  Printf.printf  "Execution time : %fs \n" (Sys.time() -. t);
  fx
;;

(** Ajoute premier element de A dans B **)
let add(a, b : fich list * fich list) : fich list =

  if empty a
  then failwith ("ERROR <add> : Liste d'entr�e A est vide")
  else fst(a) :: b
;;

let rec merge_string(l1, l2 : string list * string list)
        : string list =
  if empty l1
  then l2
  else
    if empty l2
    then l1
    else
      if fst l1 = fst l2
        then fst l1 :: merge_string(res l1, res l2) 
        else
          if fst l1 < fst l2
          then fst l1 :: merge_string(res l1, l2)
          else  fst l2 :: merge_string(l1 ,res l2)
;;

let print_fich_list(f : fich list) : unit =

  if empty f
  then Printf.printf "%s\n" "Pas d'élément"
  else
    let l : fich list ref = ref f
    in
    Printf.printf "%s" "[";
  while not (empty (!l))
  do
    if empty (res !l)
    then
      (
        Printf.printf "(%s, " (user !l);
        Printf.printf "%s)]" (pw !l);
        l := res(!l)
      )
    else
      (
        Printf.printf "(%s, " (user !l);
        Printf.printf "%s);\n" (pw !l);
        l := res(!l)
      )
    
  done
    

let print_list(s : string list) : unit =

  if empty s
  then Printf.printf "%s\n" "Pas d'élément"
  else
    let r : string list ref = ref s in
    Printf.printf "%s" "[";
  while not (empty (!r))
  do
    if empty (res !r)
    then Printf.printf "%s]" (fst !r)
    else Printf.printf "%s; " (fst !r);
    r := res(!r);
  done
;;

let print_list_list(l : string list list) : unit =

  if empty l
  then Printf.printf "%s\n" "Pas d'élément"
  else
  let li : string list list ref = ref l in
   Printf.printf "%s" "[";
  while not (empty (!li))
  do
    if empty (res !li)
    then
      (
        print_list(fst !li);        
        Printf.printf "%s" "]";
      )        
    else print_list(fst !li);

    Printf.printf "\n";
    li := res(!li);
  done
;;
  