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

[@bs.module "react-native/Libraries/Core/Devtools/openURLInBrowser"]
external openURLInBrowser: string => unit = "default";

module Header = {
  [@react.component] [@bs.module "react-native/Libraries/NewAppScreen"]
  external make: _ => React.element = "Header";
};

/*
 =========
 BINDING
 =========
 */
type timerID;
[@bs.val] external setTimeout: (unit => unit, int) => timerID = "setTimeout";
[@bs.val] external clearTimeout: timerID => unit = "setTimeout";

/*
 Here is StyleSheet that is using Style module to define styles for your components
 The main different with JavaScript components you may encounter in React Native
 is the fact that they **must** be defined before being referenced
 (so before actual component definitions)
 More at https://reasonml-community.github.io/reason-react-native/en/docs/apis/Style/
 */

let styles =
  Style.(
    StyleSheet.create({
      "root": style(~flex=1., ()),
      "simpleNav": style(~flex=0.1, ~backgroundColor=colors##black, ()),
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

module Sos = {
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
};

[@react.component]
let app = () => {
  <> <StatusBar barStyle=`lightContent /> <Sos /> </>;
};
