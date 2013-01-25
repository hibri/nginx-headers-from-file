#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

static char *ngx_http_add_headers_from_file(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_add_headers_from_file_filter_init(ngx_conf_t *cf);

typedef struct {
    ngx_str_t                           headers_file;
} ngx_http_headers_file_t;

static ngx_command_t  ngx_http_add_headers_from_file_commands[] = {

  { ngx_string("add_headers_from_file"),
    NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
    ngx_http_add_headers_from_file,
    NGX_HTTP_LOC_CONF_OFFSET,
    0,
    NULL },

    ngx_null_command
};


//static u_char  ngx_hello_world[] = "hello world";

static ngx_http_module_t  ngx_http_add_headers_from_file_ctx = {
  NULL,                          /* preconfiguration */
  ngx_http_add_headers_from_file_filter_init,                          /* postconfiguration */

  NULL,                          /* create main configuration */
  NULL,                          /* init main configuration */

  NULL,                          /* create server configuration */
  NULL,                          /* merge server configuration */

  NULL,                          /* create location configuration */
  NULL                           /* merge location configuration */
};


ngx_module_t ngx_http_add_headers_from_file_filter = {
  NGX_MODULE_V1,
  &ngx_http_add_headers_from_file_ctx, /* module context */
  ngx_http_add_headers_from_file_commands,   /* module directives */
  NGX_HTTP_MODULE,               /* module type */
  NULL,                          /* init master */
  NULL,                          /* init module */
  NULL,                          /* init process */
  NULL,                          /* init thread */
  NULL,                          /* exit thread */
  NULL,                          /* exit process */
  NULL,                          /* exit master */
  NGX_MODULE_V1_PADDING
};

static ngx_http_output_header_filter_pt ngx_http_next_header_filter;
static ngx_http_output_body_filter_pt   ngx_http_next_body_filter;


static ngx_int_t ngx_http_add_headers_from_file_filter_handler(ngx_http_request_t *r)
{
  

  r->headers_out.content_type.len = sizeof("text/funky") - 1;
  r->headers_out.content_type.data = (u_char *) "text/funky";
  
  //
  ngx_table_elt_t  *h;

   
  h = ngx_list_push(&r->headers_out.headers);
  if (h == NULL) {
      return NGX_ERROR;
  }

  h->hash = 1;
  ngx_str_set(&h->key, "X-Hibri");

  
  h->value.len = sizeof("My Header Value") -1;
  h->value.data = (u_char *) "My Header Value";

  //call the next filter in the chain
  return ngx_http_next_header_filter(r);
}


static char *ngx_http_add_headers_from_file(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
  //this is where we need to read the configuration but not needed right now
  //ngx_http_core_loc_conf_t  *clcf;

  //clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
  

  return NGX_CONF_OK;
}

static ngx_int_t ngx_http_add_headers_from_file_filter_init(ngx_conf_t *cf)
{
    ngx_http_next_header_filter = ngx_http_top_header_filter;
    ngx_http_top_header_filter = ngx_http_add_headers_from_file_filter_handler;

    ngx_http_next_body_filter = ngx_http_top_body_filter;
    ngx_http_top_body_filter = ngx_http_top_body_filter;
    return NGX_OK;
}

