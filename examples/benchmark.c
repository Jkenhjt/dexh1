#include <stdio.h>
#include <string.h>
#include <time.h>

#include <dexh1/hash_table.h>
#include <dexh1/http.h>


clock_t benchmark_request()
{
  clock_t t1, t2;
  char* request = "POST /api/v1/benchmark/parse-test?param1=alpha&param2=beta&param3=gamma&param4=delta&param5=epsilon&param6=zeta&param7=eta&param8=theta&param9=iota&param10=kappa&param11=lambda&param12=mu&param13=nu&param14=xi&param15=omicron&param16=pi&param17=rho&param18=sigma&param19=tau&param20=upsilon HTTP/1.1\r\n"
                  "Host: benchmark-target.local:8080\r\n"
                  "User-Agent: ParserBenchmarkClient/4.2.0 (High-Throughput-Stress-Runner)\r\n"
                  "Accept: application/json, text/plain, */*\r\n"
                  "Accept-Language: en-US,en;q=0.9\r\n"
                  "Accept-Encoding: gzip, deflate, br\r\n"
                  "Connection: keep-alive\r\n"
                  "Cache-Control: no-cache\r\n"
                  "Pragma: no-cache\r\n"
                  "Content-Type: application/json\r\n"
                  "Content-Length: 1024\r\n"
                  "X-Benchmark-Iteration: 99999\r\n"
                  "X-Client-UUID: 550e8400-e29b-41d4-a716-446655440000\r\n"
                  "X-Custom-Header-001: value_string_alpha_001\r\n"
                  "X-Custom-Header-002: value_string_beta_002\r\n"
                  "X-Custom-Header-003: value_string_gamma_003\r\n"
                  "X-Custom-Header-004: value_string_delta_004\r\n"
                  "X-Custom-Header-005: value_string_epsilon_005\r\n"
                  "X-Custom-Header-006: value_string_zeta_006\r\n"
                  "X-Custom-Header-007: value_string_eta_007\r\n"
                  "X-Custom-Header-008: value_string_theta_008\r\n"
                  "X-Custom-Header-009: value_string_iota_009\r\n"
                  "X-Custom-Header-010: value_string_kappa_010\r\n"
                  "X-Custom-Header-011: value_string_lambda_011\r\n"
                  "X-Custom-Header-012: value_string_mu_012\r\n"
                  "X-Custom-Header-013: value_string_nu_013\r\n"
                  "X-Custom-Header-014: value_string_xi_014\r\n"
                  "X-Custom-Header-015: value_string_omicron_015\r\n"
                  "X-Custom-Header-016: value_string_pi_016\r\n"
                  "X-Custom-Header-017: value_string_rho_017\r\n"
                  "X-Custom-Header-018: value_string_sigma_018\r\n"
                  "X-Custom-Header-019: value_string_tau_019\r\n"
                  "X-Custom-Header-020: value_string_upsilon_020\r\n"
                  "X-Custom-Header-021: value_string_phi_021\r\n"
                  "X-Custom-Header-022: value_string_chi_022\r\n"
                  "X-Custom-Header-023: value_string_psi_023\r\n"
                  "X-Custom-Header-024: value_string_omega_024\r\n"
                  "X-Trace-Parent: 00-4bf92f3577b34da6a3ce929d0e0e4736-00f067aa0ba902b7-01\r\n"
                  "X-Forwarded-For: 203.0.113.195, 70.41.3.18, 150.172.238.178\r\n"
                  "X-Forwarded-Proto: https\r\n"
                  "X-Forwarded-Port: 443\r\n"
                  "\r\n"
                  "{\"test_metadata\": {\"suite\": \"parser_performance_stress\",\"version\": \"1.0.0\",\"timestamp\": 1772647620},\"payload\": {\"nested_data\": [{ \"id\": 1, \"description\": \"Lorem ipsum dolor sit amet, consectetur adipiscing elit.\" },{ \"id\": 2, \"description\": \"Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\" },{ \"id\": 3, \"description\": \"Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris.\" },{ \"id\": 4, \"description\": \"Duis aute irure dolor in reprehenderit in voluptate velit esse cillum.\" },{ \"id\": 5, \"description\": \"Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia.\" }],\"flags\": {\"enable_parsing_metrics\": true,\"strict_mode\": false,\"buffer_limit_bytes\": 65536}}}";
  t1 = clock();

  for(int i = 0; i < 10000000; i++)
  {
    dexh1_http req;

    InitDexh1(&req);

    Dexh1RequestParser(&req, request, strlen(request));

    dexh1_http_field method = Dexh1GetField(&req.ht, "method", 6);
    dexh1_http_field path = Dexh1GetField(&req.ht, "path", 4);
    dexh1_http_field http_version = Dexh1GetField(&req.ht, "http_version", 12);
    dexh1_http_field message_body = Dexh1GetField(&req.ht, "message_body", 12);
  }

  t2 = clock();

  return t2 - t1;
}

clock_t benchmark_response()
{
  return 0;
}

int main(int argc, char** argv, char** envp)
{
  clock_t request_t;
  
  printf("\nBenchmark Dexh1\n\n");
  printf("Stage [1/2]\n\n");
  printf("Request size: ~2.6kb\n");
  printf("Number fields: 30 (with first line and last is 34)\n\n");
  
  request_t = benchmark_request();

  printf("Request parsing speed: %lf / RPS\n", 1 / (((double)request_t / CLOCKS_PER_SEC) / 10000000));
}
