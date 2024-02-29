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
class End extends React.Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <div className="text-center m-auto" style={{ maxWidth: "50rem" }}>
                <h1>Thanks for Your Participation!</h1>
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
});

export default connect(
    mapStateToProps,
    mapDispatchToProps
)(End);
