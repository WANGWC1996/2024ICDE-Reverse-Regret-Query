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
class Declaration extends React.Component {
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
            <div className="text-center m-auto" style={{ maxWidth: "40rem" }}>
                <h1>Declaration</h1>
                <br />
                <br />
                <p className="lead text-left">
                    We are conducting a user study for a research project. All answers of the questions will be recorded for research purpose. The purpose is to explore critical factors for evaluating user preferences in the recommendation system.
                    <br /><br />We want to assure you that any data collected during this study will remain strictly confidential. We will take all necessary steps to protect your personal information and ensure that it is not shared with any unauthorized individuals or organizations.
                    <br /><br />We promise that we will not disclose any individual sensitive data that may be obtained through this study. However, we may disclose general statistics, such as the overall findings of the study, to third parties.
                    <br /><br />Your participation in this survey is voluntary, and you have the right to decline to answer any question or to withdraw from the survey at any time without any penalty or negative consequences.
                </p>
                <br />
                <p className="lead text-muted">
                    Click the "Agree" button to confirm that you have read and understood the above terms and conditions. <br />
                </p>
                <div>
                    <button
                        type="button"
                        className="btn btn-primary"
                        style={{ width: "8rem" }}
                        onClick={this.handleStart}
                    >
                        Agree
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
        dispatch(setActiveComponent("Introduction"));
    },
    toggleMask: (attr, mask) => dispatch(toggleMask(attr, mask)),
    changeMode: mode => dispatch(changeMode(mode))
});

export default connect(
    mapStateToProps,
    mapDispatchToProps
)(Declaration);
