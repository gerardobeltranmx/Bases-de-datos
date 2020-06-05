#include<stdio.h>
#include<string.h>
#include<mysql.h>
int main(int argc, char const *argv[])
{
    MYSQL *conexion; // Conexión a servidor
    MYSQL_RES *resultados; // Conjunto de resultados
    MYSQL_ROW registro; // Registro de la tabla
    char *servidor = "mysql.miservidor.mx"; // Nombre de Servidor
    char *usuario = "gerardo"; //Usuario de la base de datos
    char *contrasena = "2197abcd*"; //Contraseña del usuario
    int puerto = 3306; //Contraseña del usuario
    char *basedatos = "bancos"; // Nombre de la base de datos
     
    //Inicializando variable de conexión
    conexion = mysql_init(NULL);

    //Conexión a servidor de base de datos
    if(!mysql_real_connect(conexion, servidor, usuario, contrasena,
        basedatos, puerto, NULL, CLIENT_MULTI_STATEMENTS)){
        printf("Error: %s\n", mysql_error(conexion));
        exit(1);
    }

    // Establece la consulta a realizar
    char sql[]= "SELECT * FROM cuentas WHERE idcuenta='%s'; SELECT * FROM movimientos where idcuenta = '%s'";
    
    sprintf(sql, sql, argv[1], argv[1]);

    // Envia consulta SQL para la tabla Cuenta
    if (mysql_query(conexion, sql)){
        printf("Error: %s\n", mysql_error(conexion));
        exit(1);
    }

    // Recupera el conjunto de resultados
    resultados = mysql_store_result(conexion);
    if(resultados==NULL){
        printf("Error en la recuperación de resultados\n");
        exit(1);
    }
    
    
    // Recupera el registro del cliente
    if ((registro = mysql_fetch_row(resultados)) != NULL){
        printf("IdCuenta: %4s\n ", registro[0]);
        printf("Nombre   : %-35s\n", registro[1]);
        printf("Correo   : %-20s\n", registro[2]);
        printf("Fecha    : %-15s\n", registro[3]);
        printf("Saldo    : %8s\n",registro[4]);
   }
   else
   {
        printf ("Cliente no existe");
   }
   
// Efectúa la segunda consulta sobre movimientos
    mysql_next_result(conexion);
    resultados = mysql_store_result(conexion);
   
    // Recupera el registro del cliente
    while ((registro = mysql_fetch_row(resultados)) != NULL){
        printf("%4s", registro[0]);
        printf("%4s", registro[1]);
        printf("%-15s", registro[2]);
        printf("%2s",registro[3]);
        printf("%8s\n",registro[4]);
   }

    // Liberacion de resultados
        mysql_free_result(resultados);
    // Cierra conexión
    mysql_close(conexion);
    
    printf("Fin de conexión!!!");
    return 0;
}
