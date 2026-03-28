#use "env.ml";;

(** Merge deux listes A et B et retourne (inv_A)B **)
let rec aux_merge(a, b : fich list * fich list) : fich list =

  if empty a
  then b
  else aux_merge(next_couple(a), add(a,b))
;;

let rec merge(a, b : fich list * fich list) : fich list =

  if empty a && empty b
  then []
  else
    if empty a
    then b
    else
      if empty b
      then a
      else aux_merge(a, b)
;;


let rec merge_cmp(cmp : 'a -> 'a -> int)
          (l1 : 'a list) (l2 : 'a list) : 'a list  =
  
  if empty l1
  then l2
  else
    if empty l2
    then l1
    else 
    let x1 = fst l1 in
    let x2 = fst l2 in
    if cmp x1 x2 <= 0
    then x1 :: merge_cmp cmp (res l1) l2
    else x2 :: merge_cmp cmp l1 (res l2)
;;


let rec split(l : 'a list) : 'a list * 'a list =
  if empty l || empty(res l)
  then (l, [])
  else 
    let x = fst l in
    let xs = res l in
    let (left, right) = split (res xs) in
    (x :: left, fst xs :: right)
;;

let compare_by_user(e1 : fich) ( e2 : fich) : int =
  let (a1, b1) = e1 and (a2, b2) = e2 in
  
  if a1 < a2
  then -1
  else
    if a1 > a2
    then 1
    else 0
;;
let compare_by_pw (e1 : fich) ( e2 : fich) : int =
  let (a1, b1) = e1 and (a2, b2) = e2 in
  
  if b1 < b2
  then -1
  else
    if b1 > b2
    then 1
    else 0
;;

let compare_by_couple (e1 : fich) (e2 : fich) : int =
  let (a1, b1) = e1 and (a2, b2) = e2 in
  
  if a1 < a2
  then -1
  else
    if a1 > a2
    then 1
    else
      if b1 < b2
      then -1
      else
        if b1 > b2
        then 1
        else 0
;;

(*** Retourne une liste triée selon la fonction cmp donné ***)

let rec sort (cmp : 'a -> 'a -> int) (l : 'a list) : 'a list =
  
  if empty l || empty(res l)
  then l
  else 
    let (left, right) = split l in
    let sorted_left = sort cmp left in
    let sorted_right = sort cmp right in
    merge_cmp cmp sorted_left sorted_right
;;
