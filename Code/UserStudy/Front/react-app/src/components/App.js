import React from "react";
import Welcome from "./Welcome";
import Declaration from "./Declaration";
import Introduction from "./Introduction";
import PhaseOne from "./PhaseOne";
import Interaction from "./Interaction";
import PhaseTwo from "./PhaseTwo";
import Result from "./Result";
import End from "./End"
import { connect } from "react-redux";

function App({ activeComponent }) {
  switch (activeComponent) {
    case "Welcome":
      return <Welcome />;
    case "Declaration":
      return <Declaration />;
    case "Introduction":
      return <Introduction />
    case "PhaseOne":
      return <PhaseOne />
    case "Interaction":
      return <Interaction />;
    case "PhaseTwo":
      return <PhaseTwo />
    case "Result":
      return <Result />;
    case "End":
      return <End />;
    default:
      return <div />;
  }
}

const mapStateToProps = ({ activeComponent }) => ({
  activeComponent
});

export default connect(mapStateToProps)(App);
