#use "p_fct.ml";;

(*** Retourne l'ensembles des utilisateurs qui existent n fois dans un
     liste pour un mot de passe donné  ***)

     let get_users_for_mdp (l, m : fich list * string) : string list =

      if empty l
     then failwith ("ERROR <get_user_pw_doub> : Liste d'entrée vide")
     else
       
       let f : fich list  =
        sort compare_by_pw (get_list_out_double l)
       in
       get_element_doub_by_element pw user f m
   ;;
   
   (*** Retourne l'ensembles des mots de passe  qui existent n fois dans
        liste pour un utilisateur donné  ***)
   let get_mdps_for_user(l, u : fich list * string) : string list =
     
      if empty l
     then failwith ("ERROR <get_mdps_for_user> : Liste d'entrée vide")
     else
       
       let f : fich list  =
        sort compare_by_user (get_list_out_double l)
       in
       get_element_doub_by_element user pw f u
   ;;
   
   (*** Retourne l'ensembles des utilisateurs qui existent n fois dans une liste 
           avec leurs mots de passe dans une liste de liste sans doublons ***)
   let get_users_pws(l : fich list) : (string list) list =
   
     if empty l
     then failwith ("ERROR <get_users_pws_double> : Liste d'entrée vide")
     else
       let users : fich list ref =
         ref (sort compare_by_user (get_list_out_double l))
       and finalResult : (string list) list ref = ref []
       in
       while not (empty (!users))
       do
   
         let utilisateur : string  =  (user(!users)) in    
         let result = get_element_doub_by_element
                        user pw !users utilisateur
         in
         
         if not (empty (result))
         then
           finalResult := result :: !finalResult;
         
         if not (empty (!users)) && not(empty(next_couple(!users)))
         then users := next_element !users user
         else users := next_couple(!users)
           
       done;   
       !finalResult
   
   ;;
   
   (*** Retourne l'ensemble des users qui ont le meme mot de passe ***)
   
   let get_users_for_identiq_mdp(l : fich list) : string list list =
   
      if empty l
      then failwith ("ERROR <get_users_pws_double> : Liste d'entrée vide")
      else
        
        let mdps : fich list ref =
          ref (sort compare_by_pw (get_list_out_double l))
        and finalResult : (string list) list ref = ref []
        in
       
       while not (empty !mdps)
       do
   
         let mdp : string  =  (pw(!mdps)) in
         let result : string list  = get_element_doub_by_element
                        pw user !mdps mdp
         in
         
         if not (empty (result))
         then
           finalResult := result :: !finalResult;
         
         if not (empty (!mdps )) 
         then mdps := next_element !mdps pw
       done;
       !finalResult
   ;;
   
   (*** Retourne la liste des users dont le mot de passe existe dans les mots de passe clair ***)
   
   let get_users_for_clair_mdp_main(l : fich list) :
             (string list) list =
   
     if empty l
     then failwith "ERROR <get_users_for_clair_mdp> : Liste d'entrée vide"
     else
       let m : fich list = get_list_out_double (get_hashs
             (read_mdp_from_file "french_passwords_top20000.txt"))
       in
       if empty m       
       then  []
       else
         let f : fich list ref = ref (sort compare_by_pw l)
         and mdp : fich list ref = ref (sort compare_by_user m)
         and finalresult : string list list ref = ref []
         in
         while not(empty !mdp)
         do
   
           let result : string list =
             (res (get_element_doub_by_element pw user !f (user !mdp)))
           in
           
           if not(empty (result))
           then finalresult := (pw(! mdp) :: result) :: !finalresult;            
               mdp := next_element !mdp pw;
         done;   
         !finalresult
   ;;
   
   (*** Merge deux fichiers textes en supprimant les doublons dans les 2 listes***)
   
   let rec aux_merge_out_double(a, b, l
                 : fich list * fich list * fich list) : fich list =
   if empty a && empty b
   then l
   else
     if empty a
     then aux_merge_out_double(a, next_couple(b), fst b :: l)
     else
       if empty b
       then aux_merge_out_double(next_couple(a), b, fst a :: l)
       else
           if fst a = fst b
           then aux_merge_out_double(next_couple(a)
                                            , next_couple(b), fst a :: l) 
           else
             if fst a < fst b
             then aux_merge_out_double
                    (next_couple(a),b, fst a ::l)
             else  aux_merge_out_double (a
                              , next_couple(b), fst b ::l)
   ;;
   
   
     
     
   let rec merge_out_double(l1, l2 : fich list * fich list) : fich list =
   
     if empty l1
     then get_list_out_double (sort compare_by_couple l2)
     else
       if empty l2
       then get_list_out_double (sort compare_by_couple l1)
       else
         let a : fich list =
           get_list_out_double (sort compare_by_couple l1)
         and b : fich list =
           get_list_out_double (sort compare_by_couple l2)
         in
         aux_merge_out_double(a, b, [])
   ;;
   