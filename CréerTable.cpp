#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> // inclure sqlite3 et sa librairie

/*Il faut installer sqlite3 et aussi la libraire sqlite3, les commandes sont :
 sudo apt-get install sqlite3
 sudo apt-get install sqlite3 libsqlite3-dev

  Ensuite il faut éxécuter le programme grâce à la commande :
   g++ CréerTable.cpp -lsqlite3
   Enuite :
   ./a.out pour voir le résultat

   Le programme crée une base de donnée, crée une table, rempli la table,
   et grave à la requête sql on affiche le contenu de la recherche.
*/
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int  VariableDB;
   const char *sql;
   const char* data = "Callback function called";

   VariableDB = sqlite3_open("WifiDB.db", &db); // On ouvre une nouvelle DataBase


   // On crée la table avec les entités désirés
   sql = "CREATE TABLE Wifi("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "Fréquence           INT     NOT NULL," \
         "Nom            VARCHAR(20)    NOT NULL," \
         "AdresseMac   VARCHAR(20));";

   VariableDB = sqlite3_exec(db, sql, callback, 0, &zErrMsg);



      // On rempli la table ...
   sql = "INSERT INTO Wifi(ID,Fréquence,Nom,AdresseMAc)" \
         "VALUES (1, 32 , 'UQARSÉCURISÉ','192.169.0.0'); "
        ;

   // Éxécution de la requête
   VariableDB= sqlite3_exec(db, sql, callback, 0, &zErrMsg);


  // On selecte tout ce qu'il y a dans la table Wifi et on l'affiche
   sql = "SELECT * from Wifi";

 //Execute SQL statement
   VariableDB = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

   sqlite3_close(db);
   return 0;



}
