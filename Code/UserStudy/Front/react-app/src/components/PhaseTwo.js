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
class PhaseTwo extends React.Component {
    constructor(props) {
        super(props);
        this.inputs = {};
        this.inputs.name = React.createRef();
        this.inputs.email = React.createRef();
    }

    handleStart = () => {
        this.props.start();
    };

    handleModeChange = event => {
        this.props.changeMode(event.target.value);
    };

    render() {
        return (
            <div className="text-center m-auto" style={{ maxWidth: "40rem" }}>
                <h1>Phase Two: Evaluation</h1>
                <br />
                <br />
                <h4 >
                    You just ended phase one. We are now going to phase two Evaluation. We will present you some cars and ask you
                    whether you are interested in them. <br />
                </h4>
                <br />
                <p className="lead text-muted">
                    Click the "Continue" button to continue. <br />
                </p>
                <div>
                    <button
                        type="button"
                        className="btn btn-primary"
                        style={{ width: "8rem" }}
                        onClick={this.handleStart}
                    >
                        Continue
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
        dispatch(setActiveComponent("Result"));
    },
    toggleMask: (attr, mask) => dispatch(toggleMask(attr, mask)),
    changeMode: mode => dispatch(changeMode(mode))
});

export default connect(
    mapStateToProps,
    mapDispatchToProps
)(PhaseTwo);
