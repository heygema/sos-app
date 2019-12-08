open ReactNative;


type reactNativeNewAppScreenColors = {
  .
  "primary": string,
  "white": string,
  "lighter": string,
  "light": string,
  "black": string,
  "dark": string,
};

[@bs.module "react-native/Libraries/NewAppScreen"]
external colors: reactNativeNewAppScreenColors = "Colors";

/*
 =========
 BINDING
 =========
 */
type timerID;
[@bs.val] external setTimeout: (unit => unit, int) => timerID = "setTimeout";
[@bs.val] external clearTimeout: timerID => unit = "setTimeout";

let styles =
  Style.(
    StyleSheet.create({
      "root": style(~flex=1., ()),
      "sosText":
        style(
          ~color=colors##white,
          ~fontWeight=`bold,
          ~margin=0.->dp,
          ~transform=[|rotate(~rotate=90.->deg)|],
          ~textAlign=`center,
          ~fontSize=PixelRatio.getPixelSizeForLayoutSize(75.) |> float_of_int,
          (),
        ),

      "scrollView": style(~backgroundColor=colors##lighter, ()),
    })
  );

let timeOut: ref(option(timerID)) = ref(None);
let baseColor = {"red": "#F61D04", "black": "#000000"};

type sosDim =
  | Red
  | Black;

let unwrapColor = sosDim =>
  switch (sosDim) {
  | Red => baseColor##red
  | Black => baseColor##black
  };

let flipColor = current =>
  switch (current) {
  | Red => Black
  | Black => Red
  };

[@react.component]
let make = () => {
  // use to get the color from sosBackground array
  let (backgroundColor, setColor) = React.useState(() => Red);
  let flipConstant = 200;

  let sosText = [|"S", "O", "S"|];

  let timerID = ref(None);
  let setTime = () => {
    timerID :=
      Some(
        setTimeout(
          () => setColor(current => current |> flipColor),
          flipConstant,
        ),
      );
  };

  setTime();

  let mayClearTimeout = timerID => {
    switch (timerID) {
    | Some(timer) => clearTimeout(timer)
    | None => ()
    };
  };

  React.useEffect0(() => Some(() => mayClearTimeout(timerID^)));

  <SafeAreaView
    style=Style.(
      array([|
        styles##root,
        style(~backgroundColor=backgroundColor |> unwrapColor, ()),
      |])
    )>
    {sosText
     |> Array.mapi((i, text) =>
          <View
            key={string_of_int(i)}
            style=Style.(
              style(
                ~flex=1.,
                ~justifyContent=`center,
                ~alignItems=`center,
                (),
              )
            )>
            <Text style={styles##sosText}> {text}->React.string </Text>
          </View>
        )
     |> React.array}
  </SafeAreaView>;
};
