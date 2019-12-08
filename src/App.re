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


[@react.component]
let app = () => {
  <> <StatusBar barStyle=`lightContent /> <Sos /> </>;
};
