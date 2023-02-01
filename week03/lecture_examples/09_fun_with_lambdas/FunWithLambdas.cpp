auto main(int argc, char** argv) -> int {
  int i0 = 42;
  auto missingMutable = [&i0] { return i0++; };

//   struct CompilerKnows {
//     auto operator()() const -> int { return i0++; }
//     int i0;
//   };

//   int i1 = 42;
//   auto everyThingIsOk = [i1]() mutable { return i1++; };

//   struct CompilerKnows {
//     auto operator()() -> int { return i1++; }
//     int i1;
//   };

//   int const i2 = 42;
//   auto surprise = [i2]() mutable { return i2++; };

//   struct CompilerKnows {
//     auto operator()() -> int { return i2++; }
//     int const i2;
//   };

//   int const i3 = 42;
//   auto srslyWhy = [i3 = i3]() mutable { return i3++; };

//   struct CompilerKnows {
//     auto operator()() -> int { return i3++; }
//     int i3;
//   };
}
