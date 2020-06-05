#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
int main() {
    // Parámetros de conexión
    MYSQL *conexion; // Conexión a servidor
    MYSQL_RES *resultados; // Recuperación de resultados
    MYSQL_ROW registro; // Recuperación de registros
    char *servidor = "mysql.miservidor.mx"; // Nombre o IP del Servidor
    char *usuario = "userdb"; //Usuario de la base de datos
    char *contra= "12AB34cd*"; //Contraseña del usuario
    char *basedatos = "test"; // Nombre de la base de datos
    int puerto = 3306; // Puerto del servicio
    conexion = mysql_init(NULL); //Inicializando variable de conexión
    int i;
    // Conexión a servidor de base de datos
    if(!mysql_real_connect(conexion, servidor, usuario, contra, basedatos, puerto, NULL, 0)){
        printf("%s\n", mysql_error(conexion)); // Mensaje del posible error
        exit(1);
    }

    // información de conexión
    printf("Version del Servidor: %s\n", conexion->server_version);
    printf("Nombre de Base de Datos: %s\n", conexion->db);
    printf("Nombre del Servidor: %s\n", conexion->host);
    printf("Nombre del Usuario: %s\n", conexion->user);
    printf("Nombre del Contraseña: %s\n", conexion->passwd);
    // Ejecuta consulta SQL
    if (mysql_query(conexion, "SELECT * FROM clientes")) {
        printf("%s\n", mysql_error(conexion));
        exit(1);
    }
    // Recupera dirección de los resultados
    resultados = mysql_store_result(conexion);
    // Muestra definición de los campos
    MYSQL_FIELD *campos;
    int numCampos = mysql_num_fields(resultados);
    printf(" Num %-25s %10s %10s \n", "Nombre", "Tipo", "Tamaño");
    for(i=0; i< numCampos; i++){
        campos = mysql_fetch_field(resultados);
        printf("%4d: %-25s %10d %10lu \n", i+1, campos->name, campos->type, campos->length);
    }

    //Muestra registros de tabla
    printf("%12s %-29s %-34s\n", "Cuenta", "Nombre", "Correo");
    while ((registro = mysql_fetch_row(resultados)) != NULL){
        unsigned long *longitud = mysql_fetch_lengths(resultados);
        printf("%8s(%2lu) %-25s(%2lu) %-30s(%2lu)\n", registro[0], longitud[0] , registro[1], longitud[1],registro[2],
    longitud[2]);
    }
    printf("Lista de %d clientes\n", (int)mysql_num_rows(resultados));
    mysql_free_result(resultados); // Liberar recursos de resultados
    mysql_close(conexion); // Cierra conexión
    return 0;
}
