#use "main.ml";;

(*********************************************************************
 /////////////////////////////////////////////////////////////////////
 ********************************************************************)

let depensetout = merge_out_double(read_data_from_file
"depensetout01.txt",read_data_from_file"depensetout02.txt");;
let slogram = merge_out_double(read_data_from_file"slogram01.txt",
                               read_data_from_file"slogram02.txt");;
let tetedamis = merge_out_double(read_data_from_file"tetedamis01.txt",
                                read_data_from_file"tetedamis02.txt");;
let all = merge_out_double(slogram, tetedamis);;
let mdp20k =
  get_hashs(read_mdp_from_file "french_passwords_top20000.txt");;

(*********************************************************************
 /////////////////////////////////////////////////////////////////////
 ********************************************************************)

 let rec prog_1() : unit =
  
  
  Printf.printf "%s " "Entrer l'utilisateur rechercher : ";
 
  let s : string = read_line() in
  
  let result1 = res (get_mdps_for_user(depensetout, s)) 
  in
  
  let rslogram = ref (res(get_mdps_for_user(slogram, s)))
  and rtetedamis = ref (res(get_mdps_for_user(tetedamis, s)))
  in
  
  let frslogram : string list ref = ref []
  and frtetedamis : string list ref = ref []
  in
  
  while not (empty !rslogram)
  do
    frslogram := res(get_mdps_for_user(mdp20k, s));
    rslogram := res !rslogram;
  done;

  while not (empty !rtetedamis)
  do
    frtetedamis := res(get_mdps_for_user(mdp20k, s));
    rtetedamis := res !rtetedamis;
  done;
  
  

  Printf.printf "%s\n" "Depensetout : ";
  print_list(result1);
  Printf.printf "\n";

  Printf.printf "%s\n" "slogram : ";
  print_list(!frslogram);
  Printf.printf "\n";

  Printf.printf "%s\n" "tetedamis : ";
  print_list(!frtetedamis);
  Printf.printf "\n";

  Printf.printf "\n\n%s\n\n" "***********//////////////***************";
  go_back ();
  crack()
  


and prog_2() : unit =

  Printf.printf "%s " "Entrer le mot de passe recherché : ";

  let s : string = read_line() in
  
  let result1 = res (get_users_for_mdp(depensetout, s)) 
  and m = hash(s)
  in
  
  let (a,b) = m
  in
  
  let rslogram = res(get_users_for_mdp(slogram, a))
  and rtetedamis = res(get_users_for_mdp(tetedamis, a))
  in
  

  Printf.printf "%s\n" "Depensetout : ";
  print_list(result1);
  Printf.printf "\n";

  Printf.printf "%s\n" "slogram : ";
  print_list(rslogram);
  Printf.printf "\n";

  Printf.printf "%s\n" "tetedamis : ";
  print_list(rtetedamis);
  Printf.printf "\n";
  
Printf.printf "\n\n%s\n\n" "***********//////////////***************";
go_back ();
crack()

  

and prog_3() : unit =

  print_fich_list(depensetout);
  print_list_list(get_users_for_clair_mdp_main(all));

 Printf.printf "\n\n%s\n\n" "***********//////////////***************";
 go_back ();
 crack()
  


and prog_01() : unit =
  
  print_fich_list(merge_out_double(test01,test02));


 Printf.printf "\n\n%s\n\n" "***********//////////////***************";
 go_back ();
 crack()


and prog_02() : unit =
  
  Printf.printf "%s " "Entrer l'utilisateur rechercher : ";
 
  let s : string = read_line() in
  
  let result1 = res (get_mdps_for_user(test01, s))
  and result2 = res (get_mdps_for_user(test02, s))
  in
  
  let result3  = merge_string(result1, result2)
  in

  Printf.printf "%s " "Test01 : ";
  print_list(result1);

  Printf.printf "\n %s " "Test02 : ";
  print_list(result2);

  if identiq_psw(result3)
  then Printf.printf "\n %s " "les mots de passes sont identiques"
  else Printf.printf "\n %s " "les mots de passes ne sont pas identiques";

Printf.printf "\n\n%s\n\n" " ***********//////////////***************";
go_back ();
crack()


and prog_03() : unit =

  Printf.printf "%s " "Entrer le mot de passe rechercher : ";

  let m : string = read_line() in

  let result1 = res (get_users_for_mdp(test01, m))
  and result2 = res (get_users_for_mdp(test02, m))
  in
  Printf.printf "%s " "Test01 : ";
  print_list(result1);

  Printf.printf "\n %s " "Test02 : ";
  print_list(result2);


 Printf.printf "\n\n%s\n\n" "***********//////////////***************";
 go_back ();
 crack()

  
and  crack() : unit =

  Printf.printf "\n\n%s\n" "Quel Programme souhaitez-vous utiliser?";
  Printf.printf "%s\n" "Entrer le nombre du programme correspondant: ";
  
  Printf.printf "\n%s\n" "Tester les fonctions travail attendu :";
  
  Printf.printf "\t%s\n" "** 10-Fusionner deux listes en éléminant les doublons ";
  Printf.printf "\t%s\n" "** 20- Les mots de passe d 'un login en plusieurs fuites de donné, et check s'ils sont identiques ";
  Printf.printf "\t%s\n" "** 30- Les utilisateurs associés à un mot de passe dans des fuites de donné. ";
  Printf.printf "\t%s\n" "** 40- Cette question est traitée dans la partie crack";

  Printf.printf "\n%s\n" "CRACK : Fonctions plus utiles :";
  Printf.printf "\t%s\n" "** 1 : Trouver tous les  mots de passes d'un utilisateurs";
  Printf.printf "\t%s\n" "** 2 : Trouver tous les utilisateurs pour mot de passe";
  Printf.printf "\t%s\n" "** 3 : L'ensemble des utilisateurs dont on a un mot de passe potentiel";
  
  Printf.printf "%s " "A vous de choisir : ";

  let n : int = read_int() in
  if n = 1
  then prog_1()
  else
    if n = 2
    then prog_2()
    else
      if n = 3
      then prog_3()
      else
         if n = 10
         then prog_01()
         else       
           if n = 20         
           then prog_02()
           else             
             if n = 30
             then prog_03()
             else
               (
                 Printf.printf "%s\n" "Mauvais choix";
                 crack()
               )
;;


let accueil() : unit =

  Printf.printf "\n%s\n" "Réponses aux questions du hacker :";
  
  Printf.printf "\n\t%s\n" "Une attaque par force brute ?";
  Printf.printf "\t\t%s\n" "L'utilisation de force brute n'est pas optimal voire même impossible.\n **craquer un mot de passe de 6 caractèrespeut prendre 3,1 * 10^-3s.\n **craquer un mot de passe de 128 caractères peut prendre  2,3 * 10^241s (plus que l’âge de l’univers).";
  
  Printf.printf "\n\t%s\n" "Une attaque par force brute partielle ?";
  Printf.printf "\t\t%s\n" "Cette approche peut être plus efficace et réalisable.Les sous-ensembles possibles :\n **Mots de Passe Courants\n **Mots de Passe Basés sur des Informations Personnelles";
  
  Printf.printf "\n\t%s\n" "D'autres piste ?";
  Printf.printf "\t%s\n" "**Utilisation des fuites de mot de passe\n\t **Attaques par Rainbow Tables\n\t **Décrypté des mots de passe hashé";

  Printf.printf "\n\n%s\n" "Travail attendu :";
  Printf.printf "\n\t%s\n" "On va utiliser comme exemple deux fichiers :";
  Printf.printf "\n%s\n" "test01 :";
  print_fich_list(read_data_from_file("test01.txt"));
  Printf.printf "\n\n%s\n" "test02 :";
  print_fich_list(read_data_from_file("test02.txt"));
  Printf.printf "\n";
  Printf.printf "Appuyez sur Entrer pour éxécuter le crack...\n";
  ignore (read_line ());
  crack()
  
;;