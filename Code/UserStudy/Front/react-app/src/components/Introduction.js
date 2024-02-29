import React from "react";
import {
  setActiveComponent,
  setCandidates,
  toggleMask,
  changeMode
} from "../actions";
import { connect } from "react-redux";
import { selectCandidates } from "../utils";



// the welcome scene containing a brief introduction and a table to obtain the user's input
class Introduction extends React.Component {
  constructor(props) {
    super(props);
  }

  handleStart = () => {
    this.props.start();
  };

  handleModeChange = event => {
    this.props.changeMode(event.target.value);
  };

  render() {
    return (
      <div className="text-center m-auto" style={{ maxWidth: "50rem" }}>
        <h1>Instructions</h1>
        <br />
        <br />
        <p className="lead text-left" style={{fontSize: "30px"}}>
          There are two phases: Interaction and Evaluation. <br />
        </p>
        <p className="lead text-left">
          Phase 1 (Interaction): In the Interaction phase, we want to ask you a few questions to learn
          your preference and then find some cars that you will be interested in. <br /><br />
          Phase 2 (Evaluation): In the Evaluation phase, we will present you some cars and ask you
          whether you are interested in them.<br /><br />
        </p>
        <p className="lead text-muted">
          Click the "Start" button to start the research project. <br />
        </p>
        <div>
          <button
            type="button"
            className="btn btn-primary"
            style={{ width: "8rem" }}
            onClick={this.handleStart}
          >
            Start
          </button>
        </div>
      </div>
    );
  }
}

const mapStateToProps = ({ attributes, mask, points, mode }) => ({
  attributes,
  mask,
  points,
  mode
});

const mapDispatchToProps = dispatch => ({
    start: () => {
        dispatch(setActiveComponent("PhaseOne"));
    },
    toggleMask: (attr, mask) => dispatch(toggleMask(attr, mask)),
    changeMode: mode => dispatch(changeMode(mode))
});

export default connect(
  mapStateToProps,
  mapDispatchToProps
)(Introduction);
