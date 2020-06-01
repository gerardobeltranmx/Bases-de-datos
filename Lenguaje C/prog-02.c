#include<stdio.h>
#include<string.h>
#include<mysql.h>
int main(int argc, char const *argv[])
{
    MYSQL *conexion; // Conexión a servidor
    MYSQL_RES *resultados; // Conjunto de resultados
    MYSQL_ROW registro; // Registro de la tabla
    char *servidor = "mysql.miservidor.mx"; // Nombre de Servidor
    char *usuario = "userdb"; //Usuario de la base de datos
    char *contrasena = "12AB34cd*"; //Contraseña del usuario
    int puerto = 3306; //Contraseña del usuario
    char *basedatos = "test"; // Nombre de la base de datos
     
    //Inicializando variable de conexión
    conexion = mysql_init(NULL);

    //Conexión a servidor de base de datos
    if(!mysql_real_connect(conexion, servidor, usuario, contrasena,
        basedatos, puerto, NULL, 0)){
        printf("Error: %s\n", mysql_error(conexion));
        exit(1);
    }

    // Establece la consulta a realizar
    char sql[100]= "SELECT * FROM clientes WHERE numCliente='%s'";
    
    // Establece los parámetros de la consulta a realizar
    sprintf(sql, sql, argv[1]);

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
    
    // Determina cuantos registros se recuperaron
    int N = (int)mysql_num_rows(resultados);   
    if(N>0){
        printf ("Se encontraron %d clientes\n",N);
    } 
    else{   
        printf("No tenemos clientes\n");
    }

    // Recupera el registro del cliente
    while ((registro = mysql_fetch_row(resultados)) != NULL){
        printf("%4s ", registro[0]);
        printf("%-35s", registro[1]);
        printf("%-20s", registro[2]);
        printf("%-15s", registro[3]);
        printf("%8s\n",registro[4]);
   }

    // Liberacion de resultados
    mysql_free_result(resultados);
    
    // Cierra conexión
    mysql_close(conexion);
    
    printf("Fin de conexión!!!\n");
    return 0;
}
