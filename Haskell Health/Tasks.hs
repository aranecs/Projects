-- =============== DO NOT MODIFY ===================

{-# LANGUAGE ExistentialQuantification #-}
{-# LANGUAGE FlexibleInstances #-}

-- ==================================================

module Tasks where

import Dataset
import Data.List
import Text.Printf
import Data.Array

type CSV = String
type Value = String
type Row = [Value]
type Table = [Row]


-- Prerequisities
split_by :: Char -> String -> [String]
split_by x = foldr op [""]
  where op char acc
            | char == x = "":acc
            | otherwise = (char:head(acc)):tail(acc)

read_csv :: CSV -> Table
read_csv = (map (split_by ',')) . (split_by '\n')

write_csv :: Table -> CSV
write_csv = (foldr (++) []).
            (intersperse "\n").
            (map (foldr (++) [])).
            (map (intersperse ","))



{-
    TASK SET 1
-}


-- Task 1

-- intoarce a / b
divide :: Int -> Int -> Float
divide a b = (fromIntegral a) / (fromIntegral b)

-- primeste o lista de string-uri. Intoarce o lista de string-uri formata din primul
-- element din lista primita si media aritmetica a celorlalte elemente
average :: [String] -> [String]
average [] = []
average x = (head x) : (printf "%.2f" (divide (sum (map (read::String->Int) (tail x))) 8)) : []

-- calculez recursiv media si o adaug in lista
compute_average_steps_rec :: Table -> Table
compute_average_steps_rec [] = []
compute_average_steps_rec tabel = average (head tabel) : compute_average_steps_rec (tail tabel)

compute_average_steps :: Table -> Table
compute_average_steps [] = []
compute_average_steps tabel = ["Name", "Average Number of Steps"] : compute_average_steps_rec (tail tabel)



-- Task 2

-- delimitez partea calculabila din lista si o transform din String in Int-uri
sum_of_steps :: [String] -> Int
sum_of_steps [] = 0
sum_of_steps x = sum (map (read::String->Int) (tail x))

-- Number of people who have achieved their goal:
get_passed_people_num :: Table -> Int
get_passed_people_num [] = 0
get_passed_people_num  tabel =  if (1000 <= sum_of_steps(head tabel)) then 1 + get_passed_people_num(tail tabel) else get_passed_people_num(tail tabel)


-- Percentage of people who have achieved their:
get_passed_people_percentage :: Table -> Float
get_passed_people_percentage [] = 0
get_passed_people_percentage tabel = divide (get_passed_people_num tabel) (length (tail tabel))


-- calculez suma elementelor din coloana 2 a tabelului
steps_sum :: Table -> Float 
steps_sum [] = 0
steps_sum tabel = (read :: String -> Float)((head tabel) !! 1) + steps_sum (tail tabel) 

-- Average number of daily steps
get_steps_avg :: Table -> Float
get_steps_avg [] = 0
get_steps_avg tabel = (steps_sum (tail (compute_average_steps tabel))) / (fromIntegral (length (tail tabel))) * 8

-- Task 3 
-- calculez pentru fiecare ora (coloana) suma pasilor 
sum_1_column :: Table -> Int
sum_1_column [] = 0
sum_1_column tabel = (read :: String -> Int)((head tabel) !! 1) + sum_1_column (tail tabel)

sum_2_column :: Table -> Int
sum_2_column [] = 0
sum_2_column tabel = (read :: String -> Int)((head tabel) !! 2) + sum_2_column (tail tabel)

sum_3_column :: Table -> Int
sum_3_column [] = 0
sum_3_column tabel = (read :: String -> Int)((head tabel) !! 3) + sum_3_column (tail tabel)

sum_4_column :: Table -> Int
sum_4_column [] = 0
sum_4_column tabel = (read :: String -> Int)((head tabel) !! 4) + sum_4_column (tail tabel)

sum_5_column :: Table -> Int
sum_5_column [] = 0
sum_5_column tabel = (read :: String -> Int)((head tabel) !! 5) + sum_5_column (tail tabel)

sum_6_column :: Table -> Int
sum_6_column [] = 0
sum_6_column tabel = (read :: String -> Int)((head tabel) !! 6) + sum_6_column (tail tabel)

sum_7_column :: Table -> Int
sum_7_column [] = 0
sum_7_column tabel = (read :: String -> Int)((head tabel) !! 7) + sum_7_column (tail tabel)

sum_8_column :: Table -> Int
sum_8_column [] = 0
sum_8_column tabel = (read :: String -> Int)((head tabel) !! 8) + sum_8_column (tail tabel)

-- calculez media pentru fiecare ora si o includ in tabel
get_avg_steps_per_h :: Table -> Table
get_avg_steps_per_h tabel = ["H10","H11","H12","H13","H14","H15","H16","H17"] : ((printf "%.2f"(divide (sum_1_column  (tail tabel)) (length (tail tabel)))) : (printf "%.2f"(divide (sum_2_column  (tail tabel)) (length (tail tabel))))  : (printf "%.2f"(divide (sum_3_column  (tail tabel)) (length (tail tabel))))  : (printf "%.2f"(divide (sum_4_column  (tail tabel)) (length (tail tabel)))) : (printf "%.2f"(divide (sum_5_column  (tail tabel)) (length (tail tabel))))  : (printf "%.2f"(divide (sum_6_column  (tail tabel)) (length (tail tabel))))   : (printf "%.2f"(divide (sum_7_column  (tail tabel)) (length (tail tabel))))  : (printf "%.2f"(divide (sum_8_column  (tail tabel)) (length (tail tabel)))) :[])  : []

-- Task 4
-- extrag coloana n din tabel
extract_nth_column :: Table -> Int -> [String]
extract_nth_column [] _ = []
extract_nth_column tabel n = ((head tabel) !! n) : (extract_nth_column (tail tabel) n)

-- calculez cate elemente din coloana se incadreaza in range : [0 - 50), [50 - 100) si [100, 500]. 
count_range :: [String] -> (Int, Int, Int)
count_range [] = (0, 0, 0)
count_range l 
	| (read ::  String -> Int)(head l) < 50 = let (a,b,c) = count_range (tail l) in (a + 1, b, c)
	| (read ::  String -> Int)(head l) < 100 = let (a,b,c) = count_range (tail l) in (a, b + 1, c)
	| otherwise = let (a,b,c) = count_range (tail l) in (a, b, c + 1)

-- convertesc elementele unui tuplu intr-o lista de string-uri
tuple2list :: (Int, Int, Int) -> [String]
tuple2list (0, 0, 0) = ["0", "0", "0"]
tuple2list (r1, r2, r3) = show r1 : show r2 : show r3 : []

get_activ_summary :: Table -> Table
get_activ_summary [] = []
get_activ_summary tabel = ["column","range1","range2","range3"] : ("VeryActiveMinutes" : (tuple2list (count_range (tail (extract_nth_column tabel 3))))) : ("FairlyActiveMinutes" : (tuple2list (count_range (tail(extract_nth_column tabel 4))))) : ("LightlyActiveMinutes" : (tuple2list (count_range (tail(extract_nth_column tabel 5))))): []


-- Task 5

-- compar doua persoane dupa numarul lor total de pasi, 
-- daca au acelasi numar de pasi ordonez alfabetic
my_compare :: [String] -> [String] -> Ordering
my_compare x y
	|(read ::  String -> Int) (x !! 1) < (read ::  String -> Int) (y !! 1) = LT
	|(read ::  String -> Int) (x !! 1) > (read ::  String -> Int) (y !! 1) = GT 
	|otherwise = if ((head x) < (head y)) then LT else GT 

-- inserez o lista in tabel
myinsertby :: ([String] -> [String] -> Ordering) -> [String] -> Table -> Table
myinsertby c x [] = [x]
myinsertby c x (y:ys) 
	| c x y == LT = x : (y:ys)
	| otherwise = y : myinsertby c x ys

-- inserez recursiv elementele unui tabel intr-un alt tabel pe care il returnez
get_ranking_rec :: Table -> Table
get_ranking_rec [] = []
get_ranking_rec tabel = myinsertby my_compare (head tabel) (get_ranking_rec (tail tabel))

-- extrag din lista primele 2 elemente
extract_from_list :: [String] -> [String]
extract_from_list [] = []
extract_from_list l = (head l) : (head (tail l)) : []

-- extrag din tabel
extract_from_table :: Table -> Table
extract_from_table [] = []
extract_from_table tabel = (extract_from_list (head tabel)) : (extract_from_table (tail tabel))

get_ranking :: Table -> Table
get_ranking [] = []
get_ranking tabel = ["Name","Total Steps"] : (get_ranking_rec (tail (extract_from_table tabel)))
 

-- Task 6
--extrag pentru primele 4h
extract_first4 :: [Int] -> [Int]
extract_first4 [] = []
extract_first4 l = (l !! 0) : (l !! 1) : (l !! 2) : (l !! 3) : []

-- extrag pentru ultimele 4h
extract_last4 :: [Int] -> [Int]
extract_last4 [] = []
extract_last4 l = (l !! 4) : (l !! 5) : (l !! 6) : (l !! 7) : []

-- calculez diferenta dintre cele 2 medii
diff_of_h :: [Int] -> Float
diff_of_h [] = 0.0
diff_of_h l = abs ((divide (sum (extract_first4 l)) 4) - (divide (sum (extract_last4 l)) 4))
 
-- intoarce un tabel cu coloane : [[nume, sum_first4, sum_last4, diff],...] NESORTAT
get_steps_diff_table_unsorted_rec :: Table -> Table
get_steps_diff_table_unsorted_rec [] = []
get_steps_diff_table_unsorted_rec tabel = ((head (head tabel)) : (printf "%.2f" (divide (sum (extract_first4 (map (read::String->Int) (tail (head tabel))))) 4)) : (printf "%.2f" (divide (sum (extract_last4 (map (read::String->Int) (tail (head tabel))))) 4)) : (printf "%.2f" (diff_of_h (map (read::String->Int) (tail (head tabel))))) : []) : (get_steps_diff_table_unsorted_rec (tail tabel))

-- compar doua persoane dupa diff, 
-- daca au aceeasi diff ordonez alfabetic
my_compare_task6 :: [String] -> [String] -> Ordering
my_compare_task6 x y
	|(read ::  String -> Float) (x !! 3) < (read ::  String -> Float) (y !! 3) = LT
	|(read ::  String -> Float) (x !! 3) > (read ::  String -> Float) (y !! 3) = GT 
	|otherwise = if ((head x) < (head y)) then LT else GT

-- sorteaza recursiv tabelul (intoarce un tabel nou format prin inserari de elemente din tabelul primit ca parametru)
sort_steps_diff_table_rec :: Table -> Table
sort_steps_diff_table_rec [] = []
sort_steps_diff_table_rec tabel = myinsertby my_compare_task6 (head tabel) (sort_steps_diff_table_rec (tail tabel))

get_steps_diff_table :: Table -> Table
get_steps_diff_table [] = []
get_steps_diff_table tabel = ["Name","Average first 4h","Average last 4h","Difference"] : (sort_steps_diff_table_rec (get_steps_diff_table_unsorted_rec (tail tabel)))


-- Task 7

-- Applies the given function to all the values
vmap :: (Value -> Value) -> Table -> Table
vmap f [] = []
vmap f tabel = (map f (head tabel)) : (vmap f (tail tabel))


-- Task 8

-- Applies the given function to all the entries
rmap :: (Row -> Row) -> [String] -> Table -> Table
rmap f s [] = []
rmap f s tabel = s : map f (tail tabel)


get_sleep_total :: Row -> Row
get_sleep_total [] = []
get_sleep_total r = (head r) : (printf "%.2f" (divide (sum (map (read :: String -> Int) (tail r))) 1)) : []
