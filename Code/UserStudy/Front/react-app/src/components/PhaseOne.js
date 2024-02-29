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
class PhaseOne extends React.Component {
    constructor(props) {
        super(props);
        this.inputs = {};
        this.props.attributes.forEach(([attr, config]) => {
            this.inputs[attr] = [React.createRef(), React.createRef()];
        });
        this.inputs.maxPoints = React.createRef();
    }

    handleStart = () => {
        const ranges = [];
        const mask = [];
        for (let i = 0; i < this.props.attributes.length; ++i) {
            const [attr, config] = this.props.attributes[i];
            const range = [config.low, config.high];
            ranges.push(range);
            mask.push(this.props.mask[attr]);
        }
        let maxPoints = 30000;

        const candidates = selectCandidates(
            this.props.points,
            ranges,
            mask,
            maxPoints
        );
        if (candidates.length === 0) {
            alert("No matching cars, try larger ranges");
            return;
        }
        this.props.startAlgorithm(candidates);
    };

    handleModeChange = event => {
        this.props.changeMode(event.target.value);
    };

    render() {
        const trs = this.props.attributes.map(([attr, config]) => {
            const disabled = this.props.mask[attr] === 0;
            const { low, high } = config;
            return (
                <tr key={attr}>
                    <td className="align-middle">{attr}</td>
                    <td>
                        <input
                            type="text"
                            className="form-control"
                            placeholder={low}
                            ref={this.inputs[attr][0]}
                            disabled={disabled}
                        />
                    </td>
                    <td>
                        <input
                            type="text"
                            className="form-control"
                            placeholder={high}
                            ref={this.inputs[attr][1]}
                            disabled={disabled}
                        />
                    </td>
                    <td className="align-middle hidden">
                        <input
                            type="checkbox"
                            checked={disabled}
                            onChange={() =>
                                this.props.toggleMask(attr, 1 - this.props.mask[attr])
                            }
                        />
                    </td>
                </tr>
            );
        });
        trs.push(
            <tr key="other">
                <td className="align-middle font-weight-bold">Max No. of Cars</td>
                <td>
                    <input
                        type="text"
                        className="form-control"
                        placeholder="1000"
                        ref={this.inputs.maxPoints}
                    />
                </td>
                <td>
                    <div className="col form-inline align-items-center">
                        <label className="mr-4 col-form-label font-weight-bold">Mode</label>
                        <div className="mr-3 form-check form-check-inline">
                            <input
                                className="form-check-input"
                                type="radio"
                                name="inlineRadioOptions"
                                id="simplex"
                                value="simplex"
                                checked={this.props.mode === "simplex"}
                                onChange={this.handleModeChange}
                            />
                            <label className="form-check-label" htmlFor="simplex">
                                Simplex
                            </label>
                        </div>
                        <div className="form-check form-check-inline">
                            <input
                                className="form-check-input"
                                type="radio"
                                name="inlineRadioOptions"
                                id="random"
                                value="random"
                                checked={this.props.mode === "random"}
                                onChange={this.handleModeChange}
                            />
                            <label className="form-check-label" htmlFor="random">
                                Random
                            </label>
                        </div>
                    </div>
                </td>
                <td />
            </tr>
        );
        return (
            <div className="text-center m-auto" style={{ maxWidth: "40rem" }}>
                <h1>Phase One: Interaction</h1>
                <br />
                <br />
                <h4 >
                    You are now in phase one Interaction. You will be asked with multiple questions to find your favorite cars. <br />
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
    startAlgorithm: candidates => {
        dispatch(setCandidates(candidates));
        dispatch(setActiveComponent("Interaction"));
    },
    toggleMask: (attr, mask) => dispatch(toggleMask(attr, mask)),
    changeMode: mode => dispatch(changeMode(mode))
});

export default connect(
    mapStateToProps,
    mapDispatchToProps
)(PhaseOne);