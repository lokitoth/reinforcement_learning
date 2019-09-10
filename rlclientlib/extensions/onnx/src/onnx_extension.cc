
#include "model_mgmt.h"
#include "configuration.h"
#include "factory_resolver.h"
#include "constants.h"

#include "onnx_extension.h"
#include "onnx_model.h"
#include "err_constants.h"
#include "api_status.h"

namespace m = reinforcement_learning::model_management;
namespace u = reinforcement_learning::utility;

namespace reinforcement_learning { namespace onnx {

  int create_onnx_model(m::i_model** retval, const u::configuration& config, i_trace* trace_logger, api_status* status)
  {
    const char* app_id = config.get(name::APP_ID, "");
    const char* output_name = config.get(name::ONNX_OUTPUT_NAME, nullptr);
    if (output_name == nullptr)
    {
      RETURN_ERROR_LS(trace_logger, status, inference_configuration_error) << "Output name is not provided in the configuration.";
    }

    int onnx_threadpool_size = config.get_int(name::ONNX_THREADPOOL_SIZE, 10);
    bool parse_feature_string = config.get_bool(name::ONNX_PARSE_FEATURE_STRING, true);
  
    *retval = new onnx_model(trace_logger, app_id, output_name, onnx_threadpool_size, parse_feature_string);

    return error_code::success;
  };
  
  void register_onnx_factory()
  {
    model_factory.register_type(value::ONNXRUNTIME_MODEL, create_onnx_model);
  }
}}