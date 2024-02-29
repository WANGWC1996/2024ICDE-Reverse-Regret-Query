import React from "react";
import {
  setActiveComponent,
  setCandidates,
  toggleMask,
  changeMode,
  setUserName,
  setUserEmail
} from "../actions";
import { connect } from "react-redux";
import { selectCandidates } from "../utils";



// the welcome scene containing a brief introduction and a table to obtain the user's input
class Welcome extends React.Component {
  constructor(props) {
    super(props);
    this.inputs = {};
    this.inputs.name = React.createRef();
    this.inputs.email = React.createRef();
  }

  handleStart = () => {
      const strName = this.inputs.name.current.value.trim();
      const strEmail = this.inputs.email.current.value.trim();
      if (strName === "")
      {
          alert(`Please input your name.`);
          return;
      }
      else if (strEmail === "")
      {
          alert(`Please input your email address.`);
          return;
      }
      this.props.start(strName, strEmail);
  };

  handleModeChange = event => {
    this.props.changeMode(event.target.value);
  };

  render() {
    return (
      <div className="text-center m-auto" style={{ maxWidth: "50rem" }}>
        <h1>Welcome to Our Research Project!</h1>
        <br />
        <br />
          <tr key= "name">
              <td className="align-middle" style={{fontSize: "30px", textAlign: "center"}}>
                  &nbsp;
                  Please input your name:
                  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
              </td>
              <td>
                  <input
                      type="text"
                      className="form-control"
                      placeholder="Name"
                      ref={this.inputs.name}
                      style={{width: '300px'}}
                  />
              </td>
          </tr>
          <br />
          <tr key= "email">
              <td className="align-middle" style={{fontSize: "30px", textAlign: "center"}}>
                  &nbsp;
                  Please input your email address:
                  &nbsp;
              </td>
              <td>
                  <input
                      type="text"
                      className="form-control"
                      placeholder="Email"
                      ref={this.inputs.email}
                      style={{width: '300px'}}
                  />
              </td>
          </tr>
        <br />
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
  start: (strName, strEmail) => {
    dispatch(setUserName(strName));
    dispatch(setUserEmail(strEmail));
    dispatch(setActiveComponent("Declaration"));
  },
  toggleMask: (attr, mask) => dispatch(toggleMask(attr, mask)),
  changeMode: mode => dispatch(changeMode(mode))
});

export default connect(
  mapStateToProps,
  mapDispatchToProps
)(Welcome);
