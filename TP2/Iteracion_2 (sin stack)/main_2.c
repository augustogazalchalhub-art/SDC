#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

extern long calcular_gini(float gini_in);

struct memoria {char *buffer; size_t tamaño;};

static size_t escribirMemoria(void *contents, size_t size, size_t nmemb, void *userp) 
{
    size_t realsize = size * nmemb;
    struct memoria *mem = (struct memoria *)userp;
    char *ptr = realloc(mem->buffer, mem->tamaño + realsize + 1);
    if(!ptr) return 0;
    mem->buffer = ptr;
    memcpy(&(mem->buffer[mem->tamaño]), contents, realsize);
    mem->tamaño += realsize;
    mem->buffer[mem->tamaño] = 0;
    return realsize;
}

int main(void) 
{
    CURL *curl;
    CURLcode res;
    struct memoria chunk;
    chunk.buffer = malloc(1);
    chunk.tamaño = 0;

    curl = curl_easy_init();
    if(curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.worldbank.org/v2/en/country/all/indicator/SI.POV.GINI?format=json&date=2011:2020&per_page=32500&page=1&country=%22Argentina%22");        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, escribirMemoria);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        
        res = curl_easy_perform(curl);
        
        if(res == CURLE_OK) 
        {
            char *pos = strstr(chunk.buffer, "\"ARG\"");
            if (pos) {
                int fecha = 0;
                char *pos_fecha = strstr(pos, "\"date\":\"");
                if (pos_fecha) 
                {
                    sscanf(pos_fecha, "\"date\":\"%d\"", &fecha);
                }
                
                pos = strstr(pos, "\"value\":");
                if (pos) 
                {
                    float gini_float = 0.0;
                    sscanf(pos, "\"value\":%f", &gini_float);
                    
                    printf("GINI Argentina %d (float): %.2f\n", fecha, gini_float);
                    
                    long gini_final = calcular_gini(gini_float);
                    
                    printf("GINI Argentina %d (entero) + 1: %ld\n\n", fecha, gini_final);
                }
            }
        } else {
            fprintf(stderr, "Error en la petición: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }
    free(chunk.buffer);
    return 0;
}