#include <wasm_spec_tests.hpp>

const string wasm_str_f32_cmp_0 = base_dir + "/" + WASM_SPEC_TESTS_DIR + "/generated-tests/wasms/f32_cmp.0.wasm";
std::vector<uint8_t> wasm_f32_cmp_0= read_wasm(wasm_str_f32_cmp_0.c_str());

BOOST_DATA_TEST_CASE(f32_cmp_0_pass, boost::unit_test::data::xrange(0,24), index) { try {
   TESTER tester;
   tester.produce_block();
   tester.create_account( "wasmtest"_n );
   tester.produce_block();
   tester.set_code("wasmtest"_n, wasm_f32_cmp_0);
   tester.produce_block();

   action test;
   test.account = "wasmtest"_n;
   test.name = account_name((uint64_t)index);
   test.authorization = {{"wasmtest"_n, config::active_name}};

   push_action(tester, std::move(test), "wasmtest"_n.to_uint64_t());
   tester.produce_block();
   BOOST_REQUIRE_EQUAL( tester.validate(), true );
} FC_LOG_AND_RETHROW() }
