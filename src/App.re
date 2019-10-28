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

// binding here
type timerID;
[@bs.val] external setTimeout: (unit => unit, int) => timerID = "setTimeout";

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
      "root":
        style(
          ~flex=1.,
          ~justifyContent=`center,
          ~padding=15.->pct,
          ~alignItems=`center,
          (),
        ),
      "simpleNav": style(~flex=0.1, ~backgroundColor=colors##black, ()),
      "sosText":
        style(
          ~color=colors##white,
          ~fontWeight=`bold,
          ~margin=0.->dp,
          ~transform=[|rotate(~rotate=90.->deg)|],
          ~textAlign=`center,
          ~fontSize=PixelRatio.getPixelSizeForLayoutSize(50.) |> float_of_int,
          (),
        ),

      "scrollView": style(~backgroundColor=colors##lighter, ()),
    })
  );

module Sos = {
  let timeOut: ref(option(timerID)) = ref(None);

  type sosDim =
    | Red
    | Black;

  let unwrapColor = sosDim =>
    switch (sosDim) {
    | Red => "#F61D04"
    | Black => "#000000"
    };

  [@react.component]
  let make = () => {
    // use to get the color from sosBackground array
    let (backgroundColor, setColor) = React.useState(() => Red);

    let sosText = [|"S", ".", "O", ".", "S"|];

    <View
      style=Style.(
        array([|
          styles##root,
          style(~backgroundColor=backgroundColor |> unwrapColor, ()),
        |])
      )>
      {sosText
       |> Array.mapi((i, text) =>
            <Text key={string_of_int(i)} style={styles##sosText}>
              {text}->React.string
            </Text>
          )
       |> React.array}
    </View>;
  };
};

[@react.component]
let app = () => {
  <>
    <StatusBar barStyle=`lightContent />
    <SafeAreaView
      style=Style.(style(~flex=1., ~backgroundColor=colors##black, ()))>
      <Sos />
      <View style={styles##simpleNav} />
    </SafeAreaView>
  </>;
};