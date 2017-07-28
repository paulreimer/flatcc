#include <stdio.h>
#include "issue50_json_parser.h"
#include "issue50_json_printer.h"
#include "issue50_verifier.h"

#include "flatcc/support/hexdump.h"

#define UQL FLATCC_JSON_PARSE_ALLOW_UNQUOTED_LIST
#define UQ FLATCC_JSON_PARSE_ALLOW_UNQUOTED

#undef ns
//#define ns(x) FLATBUFFERS_WRAP_NAMESPACE(issue50, x)
#define ns(x) (x)

int issue50_test_json(char *json, char *expect, int expect_err, int parse_flags, int print_flags, int line)
{
    int ret = -1;
    int err;
    void *flatbuffer = 0;
    char *buf = 0;
    size_t flatbuffer_size, buf_size;
    flatcc_builder_t builder, *B;
    flatcc_json_parser_t parser;
    flatcc_json_printer_t printer;
    int i;

    B = &builder;
    flatcc_builder_init(B);
    flatcc_json_printer_init_dynamic_buffer(&printer, 0);
    flatcc_json_printer_set_flags(&printer, print_flags);

    err = issue50_parse_json(B, &parser, json, strlen(json), parse_flags);
    if (err != expect_err) {
        if (expect_err)
        {
            if( err )
            {
                fprintf(stderr, "%d: issue50: parse failed with: %s\n", line, flatcc_json_parser_error_string(err));
                fprintf(stderr, "but expected to fail with: %s\n", flatcc_json_parser_error_string(expect_err));
                fprintf(stderr, "%s\n", json);
            }
            else
            {
                fprintf(stderr, "%d: issue50: parse successful, but expected to fail with: %s\n", line, flatcc_json_parser_error_string(expect_err));
                fprintf(stderr, "%s\n", json);
            }
        }
        else
        {
            fprintf(stderr, "%d: issue50: parse failed: %s\n", line, flatcc_json_parser_error_string(err));
            fprintf(stderr, "%s\n", json);
        }
        for (i = 0; i < parser.pos - 1; ++i) {
            fprintf(stderr, " ");
        }
        fprintf(stderr, "^\n");
        goto failed;
    }
    if (expect_err) {
        ret = 0;
        goto done;
    }
    flatbuffer = flatcc_builder_finalize_aligned_buffer(B, &flatbuffer_size);
    if ((ret = ns(File_verify_as_root(flatbuffer, flatbuffer_size)))) {
        fprintf(stderr, "%s:%d: buffer verification failed: %s\n", __FILE__, line, flatcc_verify_error_string(ret));
        goto failed;
    }

    ns(File_print_json_as_root(&printer, flatbuffer, flatbuffer_size, 0));
    buf = flatcc_json_printer_get_buffer(&printer, &buf_size);
    if (!buf) {
        fprintf(stderr, "issue50: could not print result\n");
        goto failed;
    }
    if (strcmp(expect, buf)) {
        fprintf(stderr, "%d: issue50: printed buffer not as expected, got:\n", line);
        fprintf(stderr, "%s\n", buf);
        fprintf(stderr, "expected:\n");
        fprintf(stderr, "%s\n", expect);
        goto failed;
    } 
    fprintf(stderr, "%d: issue50: printed buffer matched succsessfully, got:\n", line);
    fprintf(stderr, "%s\n", buf);
    ret = 0;
done:
    if (flatbuffer) {
        hexdump("parsed buffer", flatbuffer, flatbuffer_size, stderr);
    }
    if (flatbuffer) {
        aligned_free(flatbuffer);
    }
    flatcc_builder_clear(B);
    flatcc_json_printer_clear(&printer);
    return ret;
failed:
    ret = -1;
    goto done;
}

#define TEST(x, y) \
    ret |= issue50_test_json((x), (y), 0, 0, 0, __LINE__);

#define TEST_ERROR(x, err) \
    ret |= issue50_test_json((x), 0, err, 0, 0, __LINE__);

#define TEST_FLAGS(fparse, fprint, x, y) \
    ret |= issue50_test_json((x), (y), 0, (fparse), (fprint), __LINE__);


int issue50()
{
    int ret = 0;

    char *input =
        "{\n"
        "  \"any_type\": \"FileGameConf\",\n"
        "  \"any\": { }\n"
        "}\n";

    char *output = "{\"any_type\":\"FileGameConf\",\"any\":{}}";

    TEST(input, output);
    return ret;
}

int main()
{
    return issue50();
}
